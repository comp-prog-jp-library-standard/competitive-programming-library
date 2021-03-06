#!/usr/bin/env python

import argparse
import os
from pathlib import Path
import subprocess
import time
import yaml

from termcolor import colored

import aoj
import diff
import preprocessor
import sandbox


class TestSandbox(sandbox.Sandbox):
    def compile(self, path):
        # TODO: Support other languages
        source_path = self.get_path('main.cpp')
        source_path.touch(mode=0o666, exist_ok=False)
        with (source_path).open(mode='w') as f:
            f.write(preprocessor.preprocess([str(path)]))

        compiler = os.getenv('CXX', 'g++').split(' ')
        options = os.getenv('CXXFLAGS', '-std=c++14 -O2 -Wall').split(' ')
        result = self.command(
            compiler + options + ['main.cpp', '-o', './a.out'])

        if result != 0:
            print('{}: {}'.format(path, colored('Compile Error', 'cyan')))
            raise Exception('Compile Error')

    def show_result(self, result, input_path, time_duration, color):
        time_duration = round(time_duration * 1000)
        print('{}: {} ({} ms)'.format(
             input_path.name, colored(result, color), time_duration))

    def show_file(self, path):
        print('=== {} ==='.format(path.name))
        with self.get_path(path).open() as f:
            print(f.read())

    def test_single_case(self, execution, time_limit, input_path, answer_path):
        #  Args:
        #      execution (str)
        #      time_limit (int): time limit (s)
        #      input_path (pathlib.PosixPath): path to input file
        #      answer_path (pathlib.PosixPath): path to input file
        #
        #  Returns (float):
        #      maximum time duration (s)

        output_path = Path('output')
        start_time = time.time()

        exec_code = self.command(
            ['timeout', '-s', '9', str(time_limit), execution],
            stdin=self.get_path(input_path).open(),
            stdout=self.get_path(output_path).open('w'))

        time_duration = time.time() - start_time

        # Check judge status
        if exec_code in [137, 35072]:
            self.show_result('Time Limit Exceeded',
                             input_path, time_duration, 'yellow')
            self.show_file(input_path)
            self.show_file(answer_path)
            raise Exception('Time Limit Exceeded')

        elif exec_code != 0:
            self.show_result('Runtime Error',
                             input_path, time_duration, 'magenta')
            self.show_file(input_path)
            self.show_file(answer_path)
            raise Exception('Runtime Error')

        elif not diff.diff(self.get_path(answer_path),
                           self.get_path(output_path)):
            self.show_result('Wrong Answer',
                             input_path, time_duration, 'red')
            self.show_file(input_path)
            self.show_file(answer_path)
            self.show_file(output_path)
            raise Exception('Wrong Answer')

        self.show_result('OK', input_path, time_duration, 'green')
        return time_duration

    def test(self, testcase_path, time_limit):
        path = self.get_path('tests')
        path.symlink_to('..' / testcase_path, target_is_directory=True)
        testcase = set(t.stem for t in path.iterdir() if t.suffix == '.in')
        testcase_sorted = [(len(t), t) for t in testcase]
        testcase_sorted.sort()
        testcase = [t for _, t in testcase_sorted]

        path = Path('tests')
        max_time_duration = 0
        for t in testcase:
            input_path = (path / t).with_suffix('.in')
            answer_path = (path / t).with_suffix('.out')
            # TODO: Support other languages
            time_duration = self.test_single_case(
                './a.out', time_limit, input_path, answer_path)
            max_time_duration = max(max_time_duration, time_duration)

        self.get_path(path).unlink()
        self.show_result('Passed', testcase_path, max_time_duration, 'green')


def test(source_path):
    summary_path = source_path.with_suffix('.yml')
    with summary_path.open() as f:
        data = yaml.load(f)

    # TODO: Support other languages
    testcase_path = []
    time_limit = 8

    # Set time limit
    if 'time_limit' in data:
        time_limit = int(data['time_limit'])

    # Download testcase
    if 'download' in data:
        download = data['download']
        if download['site'] == 'aoj':
            problem_id = download['problem_id']
            aoj.download(problem_id)
            testcase_path.append(Path('testcases/aoj/') / problem_id)
        else:
            raise Exception('Unknown site {}'.format(download['site']))

    # Specify testcase directory
    if 'test' in data:
        testcase = data['test']
        path = testcase['path']
        if 'generate' in testcase:
            generate = testcase['generate']
            exec_code = subprocess.run([generate, path]).returncode
            if exec_code != 0:
                raise Exception('Failed to generate input files.')
        testcase_path.append(Path(path))

    # Judge
    with TestSandbox('.workspace') as sandbox:
        sandbox.compile(source_path)
        for path in testcase_path:
            sandbox.test(path, time_limit)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='diff')
    parser.add_argument('path', type=str, nargs=1, help='Path')
    args = parser.parse_args()
    path = Path(args.path[0])
    test(path)

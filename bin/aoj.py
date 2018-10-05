#!/usr/bin/env python

import argparse
from pathlib import Path
import requests
import shutil


url = 'https://judgedat.u-aizu.ac.jp/testcases'
tests_dir = Path('testcases') / 'aoj'
tmp_dir = Path('.cache')

error_mes = [
    '/* Test case #{1} for problem {0} is not available. */',
    '/* This is a single file for multiple testcases. serial should be 1. */',
]


def download_from_case_id(pid, cid):

    def check(result):
        return result.status_code == 200 and \
            all(result.text != mes.format(pid, cid) for mes in error_mes)

    path = '{}/{}/{}/'.format(url, pid, cid)
    in_result = requests.get(path + 'in')
    out_result = requests.get(path + 'out')

    if check(in_result) and check(out_result):
        with open('{}/{}.in'.format(tmp_dir, cid), mode='w') as f:
            f.write(in_result.text)
        with open('{}/{}.out'.format(tmp_dir, cid), mode='w') as f:
            f.write(out_result.text)
        return True
    else:
        return False


def download(pid, redownload=False):
    path = tests_dir / pid
    if path.is_dir():
        if redownload:
            shutil.rmtree(path)
        else:
            print('Downloading {} skipped.'.format(pid))
            return

    print('Downloading {}...'.format(pid))

    if tmp_dir.exists() and tmp_dir.is_dir():
        shutil.rmtree(tmp_dir)

    tmp_dir.mkdir(parents=True)
    case_num = 0

    for cid in range(1, 1000):
        if download_from_case_id(pid, cid):
            case_num = cid
            print('{} #{}\r'.format(pid, cid), end='')
        else:
            break

    if case_num > 0:
        try:
            tests_dir.mkdir()
        except FileExistsError:
            pass

        shutil.move(tmp_dir, '{}/{}'.format(tests_dir, pid))
        print('Downloaded {} ({} cases).'.format(pid, case_num))

    else:
        raise Exception('Problem {} is not available'.format(pid))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('problem_id', nargs=1, help='problem ID')
    args = parser.parse_args()
    problem_id = args.problem_id[0]
    download(problem_id)

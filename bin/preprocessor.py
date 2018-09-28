#!/usr/bin/env python

import argparse
import re


def preprocess(paths):
    includes_set = set()
    result = []

    def add_template():
        prefix_list = list(set('/'.join(_.split('/')[:2]) for _ in paths))
        suffix_list = list(set(_.split('.')[-1] for _ in paths))

        if len(prefix_list) >= 2:
            raise Exception("Can't generate template {}".format(prefix_list))

        if len(suffix_list) >= 2:
            raise Exception("Can't generate template {}".format(suffix_list))

        prefix = prefix_list[0]
        suffix = suffix_list[0]
        regexp = '{{\s*LICENSE\s*}}'

        template = ''

        with open(prefix + '/src/template.' + suffix) as f:
            for line in f:
                if re.search(regexp, line) is None:
                    template += line
                else:
                    with open('LICENSE') as f_license:
                        for l in f_license:
                            template += re.sub(regexp, l.rstrip(), line)

        result.append(template + '\n\n')

    def add_file(path):
        if path not in includes_set:
            includes_set.add(path)
            with open(path) as f:
                s = f.read() + '\n\n'
            for line_no, line in enumerate(s.split('\n')):
                msg = '{} #{}'.format(path, line_no)
                parse_line(line, msg)
            result.append(s)

    def parse_line(line, msg):
        keyword = '@depends_on'
        line = line.strip()
        index = line.find('@depends_on')

        if index == -1:
            return

        path_list = line[index + len(keyword):].strip().split(' ')

        if len(path_list) == 0:
            raise Exception('Syntax Error: {}'.format(msg))

        path = path_list[0]
        add_file(path)

    add_template()

    for path in paths:
        add_file(path)

    return ''.join(result).strip()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('filepath', nargs='+', help='source files')
    args = parser.parse_args()
    result = preprocess(args.filepath)
    print(result)

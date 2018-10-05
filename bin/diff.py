#!/usr/bin/env python

import argparse


def diff_with_tolerance(expected, actual, eps):
    def is_float(s):
        if s == 'inf' or s == 'INF':
            return False
        try:
            float(s)
        except ValueError:
            return False
        return True

    def is_same_word(expected, actual):
        if is_float(expected) and is_float(actual):
            e = float(expected)
            a = float(actual)
            return abs(e - a) < eps or abs(a / e - 1) < eps
        else:
            return expected == actual

    def is_same_line(expected, actual):
        return all(is_same_word(e, a) for e, a
                   in zip(expected.split(' '), actual.split(' ')))

    return all(is_same_line(e, a) for e, a
               in zip(expected.split('\n'), actual.split('\n')))


def diff(expected_path, actual_path, diff_type='strict', param=None):
    with expected_path.open() as f:
        expected = f.read()
    with actual_path.open() as f:
        actual = f.read()

    if diff_type == 'strict':
        return expected == actual
    if diff_type == 'float':
        if param is None:
            param = 1e-6
        return diff_with_tolerance(expected, actual, param)
    raise Exception('diff_type {} is not defined.'.format(diff_type))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='diff')
    parser.add_argument('file1', type=str, nargs=1, help='Path to FILE')
    parser.add_argument('file2', type=str, nargs=1, help='Path to FILE')
    args = parser.parse_args()

    file1 = args.file1[0]
    file2 = args.file2[0]

    if diff(args.file1[0], args.file2[0]):
        print('Correct')
        exit(0)
    else:
        print('Incorrect')
        exit(1)

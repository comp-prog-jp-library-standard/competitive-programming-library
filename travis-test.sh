#!/bin/bash
set -eux
# CLANG_FORMAT is the name of clang-format command we want to use
for src in `find . | grep -E "\.(cpp|h)$"`
do
    diff -u $src <($CLANG_FORMAT $src) ||
        echo "Format error: clang-format for file $src" 1>&2
done

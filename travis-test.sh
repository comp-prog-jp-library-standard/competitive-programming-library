#/bin/bash
set -eux
for src in `find . | grep -E "\.(cpp|h)$"`
do
    diff -u $src <(clang-format $src) ||
        echo "Format error: clang-format for file $src" 1>&2
done

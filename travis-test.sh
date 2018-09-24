#/bin/bash
set -eux
echo CLANG_FORMAT=$CLANG_FORMAT
for src in `find . | grep -E "\.(cpp|h)$"`
do
    diff -u $src <($CLANG_FORMAT $src) ||
        echo "Format error: clang-format for file $src" 1>&2
done

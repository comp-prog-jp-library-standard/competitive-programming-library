#!/bin/bash
# This script checks whether all *.cpp, *.h files are correctly formatted.
# This script does not make any changes to any files.
# It just prints where is ill-formatted in a diff-like style.

# CLANG_FORMAT is the name of clang-format command we want to use
if [ -z ${CLANG_FORMAT} ]
then
    CLANG_FORMAT=clang-format
fi
set -u
ERROR_COUNT=0
for src in `find . | grep -E "\.(cpp|h)$"`
do
    if ! diff -u $src <(${CLANG_FORMAT} $src)
    then
        echo "Format error: ${CLANG_FORMAT} for file $src" 1>&2
        ERROR_COUNT=`expr ${ERROR_COUNT} + 1`
    fi
done

# Print a summary
if [ ${ERROR_COUNT} -ne 0 ]
then
   echo "Error: ${ERROR_COUNT} file(s)" 1>&2
   exit 1
fi

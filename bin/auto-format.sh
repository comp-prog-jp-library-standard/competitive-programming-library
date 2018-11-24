#!/bin/bash
# This script assumes that all files are already staged.
# It formats all *.cpp, *.h files
# and check if they become different from the original ones by using git diff.
# ${CLANG_FORMAT} is the name of clang-format command we want to use.
# If not set, it defaults to "clang-format".

set -eu

if [ -z ${CLANG_FORMAT+x} ]
then
    CLANG_FORMAT=clang-format
fi

# All *.cpp/*.h files get formatted.
SOURCE_FILES=`find . | grep -E "\.(cpp|h)$"`
if ! ${CLANG_FORMAT} -i ${SOURCE_FILES}
then
    echo "${CLANG_FORMAT} failed" 1>&2
    exit 1
fi

# If git diff finds a difference, print it.
ERROR_COUNT=0
for name in `git diff --name-only`
do
    echo "File ${name} was ill-formatted and got formatted." 1>&2
    git diff ${name} 1>&2
    ERROR_COUNT=`expr ${ERROR_COUNT} + 1`
done

# Print a summary
if [ ${ERROR_COUNT} -ne 0 ]
then
   echo "Error: ${ERROR_COUNT} file(s)" 1>&2
   exit 1
fi

for TEST_FILE in `find library/cpp/tests | grep -E "\.cpp"`
do
    echo ${TEST_FILE}
    ./bin/test.py ${TEST_FILE}
done

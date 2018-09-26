#!/bin/bash
set -eu
DIRNAME=`dirname $0`
${DIRNAME}/auto-format.sh
echo OK

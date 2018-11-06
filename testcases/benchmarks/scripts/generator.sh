#!/bin/sh

set -eu

cd $1

# TODO: Cache input files
${CXX} ${CXX_FLAGS} -O2 -o exec generator.cpp
./exec
du -h *.in

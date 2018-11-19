#!/bin/sh

set -eu

cd $1

# TODO: Cache input files
${CXX} ${CXXFLAGS} -O2 -o exec generator.cpp
./exec
du -h *.in

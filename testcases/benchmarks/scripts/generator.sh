#!/bin/sh

set -eu

cd $1

${CXX} --std=c++14 -O2 -o exec generator.cpp
./exec
du -h *.in

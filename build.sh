#!/bin/bash
if [[ -z "$1" ]]; then
    cd "$(dirname "$0")"
    mkdir -p build
    cd build
    cmake -DCMAKE_C_COMPILER=/usr/bin/clang-16  -B . -S ..
    cmake --build .
    make
    exit 0
elif [[ $1 = "--tests" ]] || [[ $1 = "-t" ]]; then
    cd "$(dirname "$0")"
    mkdir -p build-tests
    cd build-tests
    cmake -DCMAKE_C_COMPILER=/usr/bin/clang-16 -B . -S ../tests
    cmake --build .
    make
    exit 0
fi

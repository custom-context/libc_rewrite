#!/bin/bash
if [[ -z "$1" ]]; then
    cd "$(dirname "$0")"
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
    make
    exit 0
fi
if [[ $1 = "--tests" ] || [ $1 = "-t" ]]; then
    cd "$(dirname "$0")"
    mkdir -p build-tests
    cd build-tests
    cmake ../tests
    cmake --build .
    make
    exit 0
fi
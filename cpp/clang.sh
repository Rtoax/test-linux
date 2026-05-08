#!/bin/bash
. ../scripts/make_tl.sh

# Default: gcc
make_tl clean
make_tl CXX=clang++ "${@}"

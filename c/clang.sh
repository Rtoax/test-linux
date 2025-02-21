#!/bin/bash
# Default: gcc
make clean
make CC=clang "${@}"

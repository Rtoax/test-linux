#!/bin/bash
set -ex

CLANG=clang

${CLANG} -cc1 -load $(pwd)/PrintFunctionNames.so -plugin print-fns hello.c

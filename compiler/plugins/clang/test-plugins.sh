#!/bin/bash
set -ex

CLANG=clang

${CLANG} -cc1 -load $(pwd)/PrintFunctionNames.so -plugin print-fns hello.c
#${CLANG} -cc1 -load $(pwd)/AnnotateFunctions.so -plugin annotate-fns hello.c
${CLANG} -cc1 -load $(pwd)/Attribute.so -plugin example -DTEST_ATTRIBUTE=1 hello.c

#!/bin/bash
set -ex

CLANG=clang

${CLANG} -cc1 -load $(pwd)/PrintFunctionNames.so -plugin print-fns hello.c -o hello-PrintFunctionNames
#${CLANG} -cc1 -load $(pwd)/AnnotateFunctions.so -plugin annotate-fns hello.c
${CLANG} -fplugin=$(pwd)/Attribute.so -DTEST_ATTRIBUTE=1 hello.c -o hello-Attribute
${CLANG} -fplugin=$(pwd)/pid.so -DTEST_PID=1 hello.c -o hello-pid

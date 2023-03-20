#!/bin/bash

clang sort.c -o sort.out
clang -O3 sort.c -o sort_optimized-O3.out
clang sort.c -o sort_instrumented.out -fprofile-instr-generate
./sort_instrumented.out 

# TODO
clang -O3 sort.c -o sort_fdo.out -fprofile-instr-use=default.profraw

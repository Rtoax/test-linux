#!/bin/bash
set -e

# GPU->Storage
./gdsio -f a.out -s 1G -x 0 -I 1
# Storage->GPU
./gdsio -f a.out -s 1G -x 0 -I 0

# CPU->Storage
./gdsio -f a.out -s 1G -x 1 -I 1
# Storage->CPU
./gdsio -f a.out -s 1G -x 1 -I 0

# GPU->CPU->Storage
./gdsio -f a.out -s 1G -x 2 -I 1
# Storage->CPU->GPU
./gdsio -f a.out -s 1G -x 2 -I 0

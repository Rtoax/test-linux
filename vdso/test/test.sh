#!/bin/bash

make time

echo "Syscall"
time ./time syscall
echo "Vsyscall"
time ./time vsyscall
echo "VDSO"
time ./time vdso

rm -f time

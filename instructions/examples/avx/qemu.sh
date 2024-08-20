#!/bin/bash

make vfmadd231ps

# TCP not support avx512
qemu-x86_64 -cpu Skylake-Server ./vfmadd231ps

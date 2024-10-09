#!/bin/bash

exe=

if [[ $1 ]]; then
	exe=$1
else
	make
	exe=latency-got
fi
LD_LIBRARY_PATH=$PWD gdb -q ${exe} < got.gdb

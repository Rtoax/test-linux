#!/bin/bash

exe=

if [[ $1 ]]; then
	exe=$1
else
	make
	exe=_GLOBAL_OFFSET_TABLE_
fi
gdb -q ${exe} < got.gdb

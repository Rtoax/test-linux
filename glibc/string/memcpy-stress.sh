#!/bin/bash
set -e

make memcpy-stress

exe=memcpy-stress
firstline=YES

[[ $1 ]] && exe=$1

for b in $(seq 16 31 4096)
do
	./${exe} --block-size ${b} --msize $((1024*1024*1024*4)) \
		${firstline:+--verbose}
	firstline=
done

#!/bin/bash
set -e

make memcpy-stress

exe=memcpy-stress
firstline=YES

[[ $1 ]] && exe=$1

echo "${exe} $(./${exe} --version)"

# To avoid some memory boundary issues, it is not a power of 2, so choose "31".
for b in $(seq 16 31 8192)
do
	./${exe} --block-size ${b} --msize $((1024*1024*1024*4)) \
		${firstline:+--verbose}
	firstline=
done

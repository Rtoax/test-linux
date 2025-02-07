#!/bin/bash
set -e

make memcpy-stress

exe=memcpy-stress
firstline=YES
msize_MB=1024*4

[[ $1 ]] && exe=$1
[[ ${RAND} ]] && msize_MB=400

echo "${exe} $(./${exe} --version)"

# To avoid some memory boundary issues, it is not a power of 2, so choose "31".
for b in $(seq 16 31 8192)
do
	./${exe} --block-size ${b} --msize $((1024*1024*${msize_MB})) \
		${firstline:+--verbose}
	firstline=
done

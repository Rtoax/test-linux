#!/bin/bash
set -e

letters=( aa bb cc dd )

# This could use to test CXL Interleave Granularity in qemu-kvm CXL emulate.
# 256 is Interleave Granularity size.
for ((i = 0; i < ${#letters[@]}; i++))
do
	x=${letters[i]}
	printf "\x${x}%.0s" {1..256} | dd of=a.bin bs=256 count=1 seek=${i} status=none
done

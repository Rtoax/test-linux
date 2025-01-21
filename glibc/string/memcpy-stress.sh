#!/bin/bash
set -e

make memcpy-stress

firstline=YES

for b in $(seq 16 31 4096)
do
	./memcpy-stress -b ${b} -s $((1024*1024*1024*4)) ${firstline:+--verbose}
	firstline=
done

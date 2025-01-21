#!/bin/bash
set -e

make memcpy-stress

for b in $(seq 16 31 4096)
do
	./memcpy-stress -b ${b}
done

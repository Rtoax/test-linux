#!/bin/bash
set -e

make memcpy-stress

for b in $(seq 16 16 2048)
do
	./memcpy-stress -b ${b}
done

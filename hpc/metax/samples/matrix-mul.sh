#!/bin/bash
set -e

readonly loop=10000

for m in $(seq 10 10 1000)
do
	./matrix-mul -m${m} -n${m} -N${loop} -i2
done

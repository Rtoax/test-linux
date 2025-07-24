#!/bin/bash
set -e

readonly loop=10000

program=$1
[[ -z ${program} ]] && program=matrix-mul

rm -f ${program}.log
for m in $(seq 10 10 1000)
do
	if [[ $m -eq 10 ]]; then
		verbose=-v
	else
		verbose=""
	fi
	./${program} -m${m} -n${m} -N${loop} -i2 ${verbose} | tee --append ${program}.log
done

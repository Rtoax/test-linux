#!/bin/bash

set -e

# man perf-list:pipeline
branches_retired=( $(perf list | grep -e ' br_') )

perf_record()
{
	local exe=$(realpath $1)
	[[ ! -e $exe ]] && echo "$exe is not exist" && exit 1
	shift

	for br in ${branches_retired[@]}
	do
		i=32
		echo -e "\033[${i}m$br\033[m"
		perf record -b -e $br -o perf.data.$(basename exe).$br -- $exe $@ 2>&1 \
			| grep -o -e '[0-9]* samples' || true
	done
}

if [[ $# -lt 1 ]]; then
	echo $0 [program]
else
	perf_record "$@"
fi

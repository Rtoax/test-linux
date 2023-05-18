#!/bin/bash

set -e

# man perf-list:pipeline
branches_retired=(
	br_inst_retired.all_branches
	br_inst_retired.all_branches_pebs
	br_inst_retired.cond_ntaken
	br_inst_retired.conditional
	br_inst_retired.far_branch
	br_inst_retired.near_call
	br_inst_retired.near_return
	br_inst_retired.near_taken
	br_inst_retired.not_taken
	br_misp_retired.all_branches
	br_misp_retired.all_branches_pebs
	br_misp_retired.conditional
	br_misp_retired.near_call
	br_misp_retired.near_taken
)

perf_record()
{
	local exe=$1

	for br in ${branches_retired[@]}
	do
		i=32
		echo -e "\033[${i}m$br\033[m"
		perf record -b -e $br -o perf.data.$exe.$br -- ./$exe 2>&1 \
			| grep -o -e '[0-9]* samples' || true
	done
}

if [[ $# -lt 1 ]]; then
	echo $0 [program]
else
	perf_record "$@"
fi

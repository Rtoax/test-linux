#!/bin/bash

stat_args="L1-dcache-load-misses"
stat_args+=",L1-icache-load-misses"
stat_args+=",LLC-load-misses"
stat_args+=",LLC-store-misses"
stat_args+=",cache-misses"
stat_args+=",branch-misses"
stat_args+=",branch-load-misses"
stat_args+=",dTLB-load-misses"
stat_args+=",dTLB-store-misses"
stat_args+=",iTLB-load-misses"
stat_args+=",node-load-misses"
stat_args+=",node-store-misses"

if [[ $# < 1 ]] || [[ ! -e $1 ]]; then
	echo "ERROR: Must specify an execution"
	exit 1
fi

exe=$1
shift
# Not absolute path
if [[ "${exe:0:2}" != "./" ]]; then
	exe=./${exe}
fi

sudo perf stat -e ${stat_args} -- ${exe} $@

#!/bin/bash


run_prefix()
{
	sudo perf stat -e L1-dcache-load-misses,L1-icache-load-misses,LLC-load-misses,LLC-store-misses,cache-misses,branch-misses,branch-load-misses,dTLB-load-misses,dTLB-store-misses,iTLB-load-misses,node-load-misses,node-store-misses -- "$@"
}

run_prefix "$@"


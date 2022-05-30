#!/bin/bash

kvm_record_host()
{
	pid=$1
	sudo perf kvm --host -o perf.data stat record -p $pid
	sudo perf kvm -i perf.data stat report
}

stat_cache_misses_0()
{
	sudo perf stat -e cache-misses -p 2373960
}

stat_cache_misses_1()
{
	pid=$1
	sudo perf stat -e L1-dcache-load-misses,L1-icache-load-misses,LLC-load-misses,LLC-store-misses,cache-misses,branch-misses,branch-load-misses,dTLB-load-misses,dTLB-store-misses,iTLB-load-misses,node-load-misses,node-store-misses -p $pid record -o perf.data
	sudo perf stat report -i perf.data

}

stat_cache_misses $@

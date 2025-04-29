#!/bin/bash
set -e

print_param() {
	local param=$1
	local fmt=%lx
	[[ $2 ]] && fmt=$2
	echo ${param} = $(printf "${fmt}\n" $(cat /sys/module/rcutree/parameters/${param}))
}

print_param jiffies_till_sched_qs
print_param blimit %ld
print_param gp_cleanup_delay %ld

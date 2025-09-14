#!/bin/bash
set -e

rcutree_param() {
	local param=$1
	local fmt=%lx
	[[ $2 ]] && fmt=$2
	echo ${param} = $(printf "${fmt}\n" $(cat /sys/module/rcutree/parameters/${param}))
}

rcupdate_param() {
	local param=$1
	local fmt=%lx
	[[ $2 ]] && fmt=$2
	echo ${param} = $(printf "${fmt}\n" $(cat /sys/module/rcupdate/parameters/${param}))
}

rcutree_param jiffies_till_sched_qs
rcutree_param blimit %ld
rcutree_param gp_cleanup_delay %ld

rcupdate_param rcu_cpu_stall_timeout %ld
rcupdate_param rcu_exp_cpu_stall_timeout %ld

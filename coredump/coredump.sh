#!/bin/bash

# run with it, generate a core.XXXX file.
function coredump() {
	ulimit -c unlimited
	echo 1 > /proc/sys/kernel/core_uses_pid
	#echo "./core.%t.%p" > /proc/sys/kernel/core_pattern
	echo "./core.%p" > /proc/sys/kernel/core_pattern
	echo 0 > /proc/sys/kernel/nmi_watchdog
	echo 1 > /sys/module/rcupdate/parameters/rcu_cpu_stall_suppress
}

if [ $# -gt 1 ]; then
	coredump
fi

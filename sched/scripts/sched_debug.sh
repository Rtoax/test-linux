#!/bin/bash

check_support()
{
	grep CONFIG_SCHED_DEBUG /boot/config-`uname -r`
}

# Count number of D processes
count_uninterruptible()
{
	awk '/\.nr_uninterruptible/ {c += $3} END {print c}' /proc/sched_debug
}

count_running()
{
	awk '/\.nr_running/ {c += $3} END{print c}' /proc/sched_debug
}

echo "Uninter: `count_uninterruptible`"
echo "Running: `count_running`"

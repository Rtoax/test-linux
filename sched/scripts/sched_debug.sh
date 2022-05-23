#!/bin/bash

# Count number of D processes
count_uninterruptible()
{
	awk '/\.nr_uninterruptible/ {c += $3} END {print c}' /proc/sched_debug
}

count_running()
{
	awk '/\.nr_running/ {c += $3} END{print c}' /proc/sched_debug
}

count_uninterruptible

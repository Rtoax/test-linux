#!/bin/bash

pidstat_mem()
{
	local pid=$$
	local interval_s=1
	local times=5

	# -s: Report stack utilization.
	# -r: Report page faults and memory utilization
	pidstat -sr -p ${pid} ${interval_s} ${times}
}

pidstat_mem

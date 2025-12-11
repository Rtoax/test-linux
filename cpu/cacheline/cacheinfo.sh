#!/bin/bash
# Get cacheline info
#
# Copyright (C) 2023-2025 Rong Tao.
#
# 2023-05-30	Rong Tao	Create this.
#

cacheline_size()
{
	printf "%-8s %-8s %-8s %-8s\n" CPU LEVEL LINE SIZE
	echo "----------------------------------"

	for cpu in /sys/devices/system/cpu/cpu[0-9]*
	do
		for idx in ${cpu}/cache/index[0-9]/
		do
			local level=$(cat $idx/level)
			local line_size=$(cat $idx/coherency_line_size)
			local size=$(cat $idx/size)
			printf "%-8s %-8s %-8s %-8s\n" $(basename $cpu) $level $line_size $size
		done
	done
}

cacheline_size

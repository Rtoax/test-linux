#!/bin/bash
# Get cacheline info
#
# Copyright (C) 2023 CESTC, Co.
#
# 2023-05-30	Rong Tao	Create this.
#

cacheline_size()
{
	echo -e "LEVEL\tSIZE"

	for idx in /sys/devices/system/cpu/cpu1/cache/index[0-9]/
	do
		level=$(cat $idx/level)
		size=$(cat $idx/coherency_line_size)
		echo -e "$level\t$size"
	done
}

cacheline_size

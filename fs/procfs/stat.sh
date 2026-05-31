#!/bin/bash
set -e

cpus=( $(grep -Eo '^cpu[0-9]+' /proc/stat) )

# see also: mpstat -P ALL
for cpu in cpu ${cpus[@]}
do
	datas=( $(grep -w ^${cpu} /proc/stat) )
	user=${datas[1]}
	nice=${datas[2]}
	system=${datas[3]}
	idle=${datas[4]}
	iowait=${datas[5]}
	irq=${datas[6]}
	softirq=${datas[7]}
	steal=${datas[8]}
	guest=${datas[9]}
	guest_nice=${datas[10]}
	echo "${cpu} ${user} ${nice} ${system} ${idle} ${iowait} ${irq} ${softirq} ${steal} ${guest} ${guest_nice}"
done

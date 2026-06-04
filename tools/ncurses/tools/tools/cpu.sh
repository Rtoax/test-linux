#!/bin/bash
# Usage: ./cpu.sh [I=<secs>]
set -e

[[ -z ${I} ]] && I=1

declare -a labels
declare -A prev_idle prev_total percent_idle

cpus=( $(grep -Eo '^cpu[0-9]+' /proc/stat) )

for cpu in all ${cpus[@]}; do
	labels+=( -l ${cpu} )
done

# ref test-linux/fs/procfs/stat.sh
while true; do
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

		total=$(( user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice ))

		if [[ ${prev_idle[$cpu]} ]]; then
			p_idle=${prev_idle[$cpu]}
			p_total=${prev_total[$cpu]}
			percent_idle[$cpu]=$(( (idle - p_idle) * 100 / (total - p_total) ))
		fi

		prev_idle[$cpu]=${idle}
		prev_total[$cpu]=${total}
	done
	if [[ ${percent_idle[@]} ]]; then
		echo "${percent_idle[@]}"
	fi
	sleep ${I}
done | ../plotcake --title 'CPU Loads %idle' --ylabel '%idle' ${labels[@]}

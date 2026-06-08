#!/bin/bash
# Usage: [I=<secs>] ./cpu.sh [cpu indexes]
# Example: I=1 ./cpu.sh 1 2 3
set -e

[[ -z ${I} ]] && I=1

indexes=( ${@} )

declare -a labels
declare -A prev_idle prev_total percent_idle
declare -a detected_cpus

readonly all_cpus=( $(grep -Eo '^cpu[0-9]+' /proc/stat) )

for i in $(seq 0 1 $((${#all_cpus[@]}-1)) ); do
	if [[ ${indexes} ]] && [[ ! " ${indexes[@]} " =~ " ${i} " ]]; then
		continue
	fi
	labels+=( -l cpu${i} )
	detected_cpus+=( cpu${i} )
done

echo ${all_cpus[@]}
echo ${detected_cpus[@]}
echo ${labels[@]}

# ref test-linux/fs/procfs/stat.sh
while true; do
	for cpu in ${detected_cpus[@]}
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
done | ../plotcake --title 'CPU Loads %idle' --ylabel '%idle' ${labels[@]} ${@}

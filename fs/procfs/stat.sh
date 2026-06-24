#!/bin/bash
# Get cpu idle percent
# see also: mpstat -P ALL 1
# Refs:
# - plotcake: test-linux/tools/ncurses/tools/tools/cpu.sh
set -e

cpus=( $(grep -Eo '^cpu[0-9]+' /proc/stat) )

[[ -z ${S} ]] && S=10

declare -A prev_idle prev_total percent_idle

for ((i = 0; i < ${S}; i++)); do
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
			# echo "(${idle} - ${prev_idle[$cpu]}) * 100 / (${total} - ${prev_total[$cpu]}) = ${percent_idle[$cpu]}%"
		fi

		# echo "${cpu} ${user} ${nice} ${system} ${idle} ${iowait} ${irq} ${softirq} ${steal} ${guest} ${guest_nice} ${total}"

		prev_idle[$cpu]=${idle}
		prev_total[$cpu]=${total}
	done
	if [[ ${percent_idle[@]} ]]; then
		echo "${percent_idle[@]}"
	fi
	sleep .1
done

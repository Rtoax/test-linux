#!/bin/bash
# Plot CPU usage
#
# see also test-linux/fs/procfs/stat.sh
#
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

declare -a labels
declare -A prev_idle prev_total percent_idle
declare -a detected_cpus
declare -a indexes

readonly all_cpus=( $(grep -Eo '^cpu[0-9]+' /proc/stat) )

declare interval_sec=1

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    plotcake-cpu - Display cpu

${BOLD}SYNOPSIS${RST}
    plotcake-cpu [options]

${BOLD}OPTIONS${RST}
    -i, --interval interval seconds of data generate, 1, 2, 0.5, 0.01
    -h, --help     show this information

${BOLD}EXAMPLES${RST}
    $ plotcake-cpu -c 0 -c 1

    test peer:
    $ taskset -c 0 bash -c 'while :; do sleep 0.002; done'
"
	exit ${1-0}
}

OPTS=$(getopt --options hi:c: \
		--long help \
		--long interval: \
		--long cpu: \
		--name plotcake-cpu -- "$@")

eval set -- "$OPTS"

while true; do
	case $1 in
	-h | --help)
		shift
		__usage__
		;;
	-i | --interval)
		shift
		interval_sec=${1}
		shift
		;;
	-c | --cpu)
		shift
		indexes+=( ${1} )
		shift
		;;
	--)
		shift
		break
		;;
	esac
done

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
	sleep ${interval_sec}
done | ${PLOTCAKE} --title 'CPU Loads %idle' --ylabel '%idle' \
	-o cpu ${labels[@]} "${@}"

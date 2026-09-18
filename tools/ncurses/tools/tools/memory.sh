#!/bin/bash
# display the memory usage
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

declare with_rss interval_sec=1

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    plotcake-memory - Display memory

${BOLD}SYNOPSIS${RST}
    plotcake-memory [--rss]

${BOLD}OPTIONS${RST}
    --rss          enable RSS
    -i, --interval interval of refresh, 1, 2, 0.5, 0.01
    -h, --help     show this information
"
	exit ${1-0}
}

OPTS=$(getopt --options hi: \
		--long help \
		--long rss \
		--long interval: \
		--name plotcake-memory -- "$@")

eval set -- "$OPTS"

while true; do
	case $1 in
	-h | --help)
		shift
		__usage__
		;;
	--rss)
		shift
		with_rss=ON
		;;
	-i | --interval)
		shift
		interval_sec=${1}
		shift
		;;
	--)
		shift
		break
		;;
	esac
done

total_rss() {
	local kB=$(ps -eo rss | awk '{sum += $1} END { print sum }')
	echo $((kB / 1024))
}

while true; do
	mem_arr=( $(free -m | grep ^Mem | awk '{print $2, $3, $4, $5, $6, $7}') )

	if [[ ${with_rss} ]]; then
		mem_arr+=( $(total_rss) )
	fi

	echo "${mem_arr[@]}"
	sleep ${interval_sec}
done | ${PLOTCAKE} --title 'Memory Usage' --xlabel 'Time' --ylabel 'Size(MB)' \
		-l total -l used -l free -l shared -l buff/cache -l avail \
		${with_rss:+ -l rss} \
		-o memory ${@}

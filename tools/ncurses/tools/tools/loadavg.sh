#!/bin/bash
# display the loadavg
#
# Usage: ./loadavg.sh [options]
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

declare interval_sec=1

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    plotcake-loadavg - Display loadavg

${BOLD}SYNOPSIS${RST}
    plotcake-loadavg [--help]

${BOLD}OPTIONS${RST}
    -i, --interval interval seconds of refresh, 1, 2, 0.5, 0.01
    -h, --help     show this information
"
	exit ${1-0}
}

OPTS=$(getopt --options hi: \
		--long help \
		--long interval: \
		--name plotcake-loadavg -- "$@")

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
	--)
		shift
		break
		;;
	esac
done

while true; do
	awk '{print $1, $2, $3}' /proc/loadavg
	sleep ${interval_sec}
done | ${PLOTCAKE} --title 'Loadavg' --xlabel 'Time' --ylabel 'Load' \
		-l 'Load1' -l 'Load5' -l 'Load15' \
		-L unicode-boldbold -L unicode-bold -L unicode \
		-C red -C blue -C white -o loadavg ${@}

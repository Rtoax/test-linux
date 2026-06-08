#!/bin/bash
# display the loadavg
#
# Usage: ./loadavg.sh [I=<secs>]
set -e

[[ -z ${I} ]] && I=1

while awk '{print $1, $2, $3}' /proc/loadavg; do
	sleep ${I}
done | ../plotcake ${args[@]} --title 'Loadavg' --xlabel 'Time' --ylabel 'Load' \
		-l 'Load1' -l 'Load5' -l 'Load15' \
		-L unicode-boldbold -L unicode-bold -L unicode \
		-C red -C blue -C white ${@}

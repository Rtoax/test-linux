#!/bin/bash
# display the process number
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

while true; do
	num=( $(ps -e | wc -l)
	      $(ps -eo state | grep ^S | wc -l)
	      $(ps -eo state | grep ^R | wc -l)
	      $(ps -eo state | grep ^I | wc -l) )
	echo ${num[@]}
	sleep 1
done | ${PLOTCAKE} --title 'Process Number' --xlabel 'Time' --ylabel 'Number' \
	-l All -l Sleep -l Run -l Idle -o process ${@}

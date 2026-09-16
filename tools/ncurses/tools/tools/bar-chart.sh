#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

data=( ${@} )
if [[ -z ${data} ]]; then
	data=( 1 2 3 2 1 )
fi
num=${#data[@]}

area_args=()
for ((i = 0; i < num; i++))
do
	area_args+=( -L unicode-area-chart )
done

for ((i = 0; i < num * 10; i++))
do
	idx=$(( i / 10 ))
	mod_idx=$(( i % 10 ))

	msg=""
	for ((j = 0; j < idx; j++))
	do
		msg+=" 0"
	done
	if [[ ${mod_idx} -lt 5 ]]; then
		msg+=" ${data[$idx]}"
	else
		msg+=" 0"
	fi
	for ((j = idx + 1; j < num; j++))
	do
		msg+=" 0"
	done

	echo "${msg}"
	sleep 0.01
done | ${PLOTCAKE} --title 'Bar chart' ${area_args[@]} -o bar-chart ${@}

#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

gpus=( $(ls-smi --show-memory | grep -oE '^GPU.[0-9]+') )

for gpu in ${gpus[@]}
do
	labels+=( -l ${gpu} )
done

while true; do
	usage=( $(ls-smi --show-memory | grep 'vis_vram usage' | awk '{print $4}') )
	echo ${usage[@]}
	sleep 0.5
done | ${PLOTCAKE} --title 'LingSpeed Memory Usage' --ylabel '100%' \
	${labels[@]} --logarithmic -o lingspeed-mem ${@}

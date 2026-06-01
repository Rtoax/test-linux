#!/bin/bash
set -e

declare -a labels
for ((i = 0; i < $(nproc); i++)); do
	labels+=( -l cpu${i} )
done

# TODO
while sleep 1; do
	loads=( $(mpstat -P ALL | grep -wv all | \
		awk '{print $NF}' | grep -E '[0-9]+\.[0-9]+') )
	echo ${loads[@]}
done | ../plotcake --title 'CPU Loads' --ylabel '%idle' ${labels[@]}

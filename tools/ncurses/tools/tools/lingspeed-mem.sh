#!/bin/bash
set -e

gpus=( $(ls-smi --show-memory | grep -oE '^GPU.[0-9]+') )

for gpu in ${gpus[@]}
do
	labels+=( -l ${gpu} )
done

while sleep 0.5; do
	usage=( $(ls-smi --show-memory | grep 'vis_vram usage' | awk '{print $4}') )
	echo ${usage[@]}
done | ../plotcake --title 'LingSpeed Memory Usage' --ylabel '100%' ${labels[@]}

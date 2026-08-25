#!/bin/bash
set -e

declare -a devices
declare -a fstypes

grub_probe=$(which grub2-probe 2>/dev/null || :)
[[ -z ${grub_probe} ]] && grub_probe=$(which grub-probe 2>/dev/null || :)

devices=( $(sudo ${grub_probe} --target=device /) )

for dev in ${devices[@]}
do
	fstypes+=( $(sudo ${grub_probe} --device ${dev} --target=fs) )
done

printf "%-32s %-8s\n" DEV FS
for ((i =0; i < ${#devices[@]}; i++))
do
	printf "%-32s %-8s\n" ${devices[$i]} ${fstypes[$i]}
done

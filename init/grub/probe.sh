#!/bin/bash

declare -a devices
declare -a fstypes

devices=( $(sudo grub2-probe --target=device /) )

for dev in ${devices[@]}
do
	fstypes+=( $(sudo grub2-probe --device ${dev} --target=fs) )
done

printf "%-32s %-8s\n" DEV FS
for ((i =0; i < ${#devices[@]}; i++))
do
	printf "%-32s %-8s\n" ${devices[$i]} ${fstypes[$i]}
done

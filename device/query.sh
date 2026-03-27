#!/bin/bash
set -e

declare -a devices pathes

devices=( $(ls /dev/ | grep -e sd[a-z]* -e vd[a-z]* -e nvme*) )

for dev in ${devices[@]}
do
	pathes+=( /sys$(udevadm info --query path --name /dev/${dev}) )
done

printf "%-24s %s\n" DEV PATH
for ((i = 0; i < ${#devices[@]}; i++))
do
	printf "%-24s %s\n" /dev/${devices[$i]} ${pathes[$i]}
done

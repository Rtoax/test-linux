#!/bin/bash
set -e

interfaces=( $(ls /sys/class/net/) )

for i in ${interfaces[@]}
do
	udevadm info /sys/class/net/${i} | sed "s|^|${i}\t|g"
done

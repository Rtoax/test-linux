#!/bin/bash
set -e

readonly DEVs=( $(ls /proc/kunlun/ | grep ^dev) )

cat /proc/kunlun/version

for dev in ${DEVs[@]}
do
	cat /proc/kunlun/${dev}/info
done

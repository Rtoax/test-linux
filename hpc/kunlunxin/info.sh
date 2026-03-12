#!/bin/bash
set -e

readonly DEVs=( $(ls /proc/kunlun/ | grep ^dev || true) )

cat /proc/kunlun/version || true

for dev in ${DEVs[@]}
do
	cat /proc/kunlun/${dev}/info || true
done

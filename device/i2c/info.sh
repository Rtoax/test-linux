#!/bin/bash
set -e

sudo i2cdetect -l

readonly dev_i2c=( $(ls /dev/i2c-* | grep -oE '/dev/i2c-[0-9]+') )

for dev in ${dev_i2c[@]}
do
	bus=$(echo ${dev} | grep -oE '[0-9]+$')
	sudo i2cdetect -y ${bus}
done

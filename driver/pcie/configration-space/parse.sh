#!/bin/bash
set -e

configs=$(ls /sys/bus/pci/devices/*/config)
slots=$(ls /sys/bus/pci/devices/)

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

for config in ${configs[@]}
do
	run ./parse --config-file ${config}
done

for slot in ${slots[@]}
do
	run ./parse --slot ${slot}
done

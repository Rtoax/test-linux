#!/bin/bash
set -e

if [[ -e /sys/firmware/fdt ]]; then
	sudo dtc -I dtb -O dts -o $PWD/a.dts /sys/firmware/fdt
fi

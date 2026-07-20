#!/bin/bash
set -e

readonly MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

run sudo cxl list
run sudo cxl list --memdevs

for dev in ${MEMDEVS[@]}
do
	run sudo cxl list -m ${dev} --health
done

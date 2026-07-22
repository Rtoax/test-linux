#!/bin/bash
set -e

readonly DECODERS=( $(sudo cxl list --decoders | jq -r '.[].decoder') )
readonly MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

run sudo cxl list
run sudo cxl list --buses
run sudo cxl list --ports
run sudo cxl list --decoders
# see commit 27dd5057a605 ("cxl: info.sh: sudo cxl list --buses --ports --decoders")
run sudo cxl list --buses --ports --decoders
run sudo cxl list --memdevs


for dev in ${MEMDEVS[@]}
do
	run sudo cxl list -m ${dev} --health
done

for decoder in ${DECODERS[@]}
do
	run sudo cxl list --decoders --decoder ${decoder}
	run sudo cxl list --memdevs --decoder ${decoder}
done

# commit a8b5d8d7094b ("cxl: ndctl list: shows bus and dimm info")
run sudo ndctl list --buses
run sudo ndctl list --dimms

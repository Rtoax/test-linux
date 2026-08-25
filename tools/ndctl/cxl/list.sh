#!/bin/bash
set -e

readonly ROOTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["root decoders"][]? | .decoder') )
readonly PORTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["port decoders"][]? | .decoder') )
readonly MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

# Check info, see commit 5a32ccae21a6 ("cxl: cxl.sh: check decoder informations")
run sudo cxl list --decoders

for decoder in ${ROOTDECODERS[@]} ${PORTDECODERS[@]}
do
	run sudo cxl list --decoders --decoder ${decoder}
	run sudo cxl list --memdevs --decoder ${decoder}
done

for memdev in ${MEMDEVS[@]}
do
	run sudo cxl list --memdev ${memdev}
done

# Bus and dimm
# commit a8b5d8d7094b ("cxl: ndctl list: shows bus and dimm info")
run sudo ndctl list --buses
run sudo ndctl list --dimms

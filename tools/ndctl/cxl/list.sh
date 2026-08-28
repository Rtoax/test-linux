#!/bin/bash
# Commits:
# - commit 1f866e735c78 ("cxl: list: 1-way vmem")
# - commit b55af6465a43 ("cxl: list: 4-ways pmem + 4-ways vmem + 4-ways vmem with dynamic capacity")
set -e

readonly ROOTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["root decoders"][]? | .decoder') )
readonly PORTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["port decoders"][]? | .decoder') )
readonly DECODERS=( $(sudo cxl list --decoders | jq -r '.[].decoder') )
readonly ALL_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )
readonly PMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("pmem_size")) | .memdev') )
readonly VMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("ram_size")) | .memdev') )
# Dynamic capacity vmem device could not see "ram_size" label.
readonly OTHER_MEMDEVS=( $(sudo cxl list --memdevs | \
			jq -r '.[] | select((has("ram_size") or has("pmem_size")) | not) | .memdev') )

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

# Check info, see commit 5a32ccae21a6 ("cxl: cxl.sh: check decoder informations")
run sudo cxl list --decoders

for decoder in ${ROOTDECODERS[@]} ${PORTDECODERS[@]} ${DECODERS[@]}
do
	run sudo cxl list --decoders --decoder ${decoder}
	run sudo cxl list --memdevs --decoder ${decoder}
done

for memdev in ${ALL_MEMDEVS[@]}
do
	run sudo cxl list --memdev ${memdev} --health
done

# Bus and dimm
# commit a8b5d8d7094b ("cxl: ndctl list: shows bus and dimm info")
run sudo ndctl list --buses
run sudo ndctl list --dimms

echo "ROOTDECODERS=\"${ROOTDECODERS[@]}\""
echo "PORTDECODERS=\"${PORTDECODERS[@]}\""
echo "DECODERS=\"${DECODERS[@]}\""
echo "ALL_MEMDEVS=\"${ALL_MEMDEVS[@]}\""
echo "PMEM_MEMDEVS=\"${PMEM_MEMDEVS[@]}\""
echo "VMEM_MEMDEVS=\"${VMEM_MEMDEVS[@]}\""
echo "OTHER_MEMDEVS=\"${OTHER_MEMDEVS[@]}\""

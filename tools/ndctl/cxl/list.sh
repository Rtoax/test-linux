#!/bin/bash
# Commits:
# - commit 1f866e735c78 ("cxl: list: 1-way vmem")
# - commit b55af6465a43 ("cxl: list: 4-ways pmem + 4-ways vmem + 4-ways vmem with dynamic capacity")
set -e

readonly MY_ROOT=$(dirname $(realpath $0))

. ${MY_ROOT}/../../../scripts/libcxl.sh

run() {
	echo -e "\033[1;32m$ sudo ${@}\033[m"
	eval sudo "${@}"
}

# commit cf0a146594a4 ("cxl: list verbose of: 4-ways pmem + 4-ways vmem + 4-ways vmem with dynamic capacity")
run cxl list --verbose

# Check info, see commit 5a32ccae21a6 ("cxl: cxl.sh: check decoder informations")
run cxl list --decoders

for decoder in ${ROOTDECODERS[@]} ${PORTDECODERS[@]} ${DECODERS[@]}
do
	run cxl list --decoders --decoder ${decoder}
	run cxl list --memdevs --decoder ${decoder}
done

for memdev in ${ALL_MEMDEVS[@]}
do
	run cxl list --memdev ${memdev} --health
done

# Bus and dimm
# commit a8b5d8d7094b ("cxl: ndctl list: shows bus and dimm info")
# commit 79942b178114 ("cxl: list: cxl list --buses .vs. ndctl list --buses")
run cxl list --buses
run ndctl list --buses
run ndctl list --dimms

cxl_info_all

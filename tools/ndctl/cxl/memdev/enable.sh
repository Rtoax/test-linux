#!/bin/bash
# Commits:
# - commit 1f866e735c78 ("cxl: list: 1-way vmem")
set -e

readonly MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )

run() {
	echo -e "\033[1;32m$ ${@}\033[m"
	eval "${@}"
}

run sudo cxl list --memdevs --health

for memdev in ${MEMDEVS[@]}
do
	run sudo cxl disable-memdev ${memdev}
	run sudo cxl list --memdevs
	run sudo cxl enable-memdev ${memdev}
done

run sudo cxl list --memdevs --health

#!/bin/bash
#
# GDSIO benchmark
#

set -e

[[ -z ${GDSIO} ]] && GDSIO=gdsio
[[ -z ${SIZE} ]] && SIZE=4G
[[ -z ${DIR} ]] && DIR="."

runprog() {
	# drop cache for each test
	echo 3 > /proc/sys/vm/drop_caches
	echo >&2 -e "\033[1;32m${@}\033[m"
	eval ${@}
}

readonly XFER_BETWEEN_STORAGE__GPU=0
readonly XFER_BETWEEN_STORAGE__CPU=1
readonly XFER_BETWEEN_STORAGE__CPU__GPU=2
readonly XFER_TYPES=(
		${XFER_BETWEEN_STORAGE__GPU}
		${XFER_BETWEEN_STORAGE__CPU}
		${XFER_BETWEEN_STORAGE__CPU__GPU}
	)

readonly OP_READ=0
readonly OP_WRITE=1

for xfer in ${XFER_TYPES[@]}
do
	for thread in 1 2 4 8 16
	do
		for op in ${OP_WRITE} ${OP_READ}
		do
			for iosize in 4K 32K 64K 128K 512K 1M 2M
			do
				runprog ./${GDSIO} -D ${DIR} -f a.out \
					-s ${SIZE} -i ${iosize} \
					-x ${xfer} -I ${op} -w ${thread}
			done
		done
	done
done

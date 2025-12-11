#!/bin/bash
#
# GDSIO benchmark
#
# Example:
# $ sudo DIR=/mnt/nvme/ SIZE=4G XFER_TYPES=0 OP_TYPES=0 gdsio_benchmark.sh

set -e

[[ -z ${GDSIO} ]] && GDSIO=gdsio # 1st choice
[[ ! -e ${GDSIO} ]] && GDSIO=gdsio-luca # 2nd choice
[[ -z ${DIR} ]] && DIR="."

# $1: logfile
runprog() {
	local logfile=$1
	shift
	# drop cache for each test
	echo 3 > /proc/sys/vm/drop_caches
	echo >&2 -e "\033[1;32m${@}\033[m"
	eval ${@} | tee --append ${logfile}
}

readonly XFER_BETWEEN_STORAGE__GPU=0
readonly XFER_BETWEEN_STORAGE__CPU=1
readonly XFER_BETWEEN_STORAGE__CPU__GPU=2
[[ -z ${XFER_TYPES} ]] && XFER_TYPES=(
		${XFER_BETWEEN_STORAGE__GPU}
		${XFER_BETWEEN_STORAGE__CPU}
		${XFER_BETWEEN_STORAGE__CPU__GPU}
	)

readonly OP_READ=0
readonly OP_WRITE=1
[[ -z ${OP_TYPES} ]] && OP_TYPES=( ${OP_READ} ${OP_WRITE} )

for xfer in ${XFER_TYPES[@]}
do
	for op in ${OP_TYPES[@]}
	do
		logfile=gdsio-x${xfer}o${op}.log

		[[ -e ${logfile} ]] && mv ${logfile} ${logfile}.old

		for thread in 1 2 4 8 16 32
		do
			for iosize in 4K 32K 64K 128K 256K 512K 1M 2M 4M
			do
				if [[ ${SIZE} ]]; then
					size=${SIZE}
				else
					# Each thread operates on the same
					# amount of data in parallel; this
					# is how the performance of the DMA
					# engine can be tested.
					size=$(( ${thread} * 512 ))M
				fi
				runprog ${logfile} \
					./${GDSIO} -D ${DIR} -f gdsio-x${xfer}-s${size}.out \
					-s ${size} -i ${iosize} \
					-x ${xfer} -I ${op} -w ${thread}
			done
		done
	done
done

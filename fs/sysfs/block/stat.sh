#!/bin/bash
# see also iostat
set -e

SYSFS="/sys/block/"
BLOCK=( $(ls ${SYSFS}) )

# $1 - block name, such as nvme0n1
handle_block() {
	local blk=$1
	local stat="${SYSFS}/${blk}"
}

for blk in ${BLOCK[@]}
do
	handle_block $blk
done

#!/bin/bash
set -e

strs=( qemu-nbd mkfs.xfs mkfs.ext4 a0.1-2 )

# Replace all special char to '_'
for str in ${strs[@]}
do
	echo "${str//[!0-9a-zA-Z]/_}"
done

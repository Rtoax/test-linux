#!/bin/bash

get_smallest_disk()
{
	local disks
	local sizes
	local minimal_size=999999999999999999
	local minimal_idx=0
	local tmpfile=$(mktemp)

	# -b: print bytes
	# TYPE=disk
	# vda, sda, hda, nvmexxx
	lsblk -b \
		| grep disk \
		| grep -e ^vd -e ^sd -e ^hd -e ^nvme \
		| awk '{print $1" "$4}' > ${tmpfile}

	while read line
	do
		local disk=$(echo $line | awk '{print $1}')
		local size=$(echo $line | awk '{print $2}')
		disks+=( $disk )
		sizes+=( $size )
	done < ${tmpfile}

	rm -f ${tmpfile}

	# For example: c is the minimal
	# disks=( a b c )
	# sizes=( 2 3 1 )
	for ((i = 0; i < ${#sizes[@]}; i++))
	do
		test ${sizes[$i]} -le $minimal_size && {
			minimal_size=${sizes[$i]}
			minimal_idx=$i
		}
	done

	echo "MinimalDisk: ${disks[$minimal_idx]}"
}

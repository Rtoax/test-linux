#!/bin/bash
set -e

blocks=(
	$(lsblk -b \
		| grep disk \
		| grep -e ^vd -e ^sd -e ^hd -e ^nvme \
		| awk '{print $1}'
	)
)

for blk in ${blocks[@]}
do
	sudo badblocks -s -v /dev/${blk}
done


#!/bin/bash

set -e

fs=rootfs.ext4
mnt=rootfs.mnt


freeze_mnt() {
	sudo fsfreeze --freeze ${mnt}
}

unfreeze_mnt() {
	sudo fsfreeze --unfreeze ${mnt}
}

create_mnt() {
	dd if=/dev/zero of=${fs} bs=1M count=1
	mkfs.ext4 ${fs}
	mkdir ${mnt}
	sudo mount ${fs} ${mnt}
}

destroy_mnt() {
	sudo umount ${mnt}
	sudo rm -rf ${mnt} ${fs}
}

# $1 - number of hung tasks
create_hung_task() {
	local nr=$1
	[[ -z $nr ]] && nr=1
	for ((i = 0; i < $nr; i++))
	do
		time cat /etc/os-release > ${mnt}/os-release &
	done
}

clean () {
	unfreeze_mnt || true
	destroy_mnt || true
}

clean

create_mnt
freeze_mnt

create_hung_task 10
echo "cat /etc/os-release hunging for 5 seconds."
sleep 5

clean

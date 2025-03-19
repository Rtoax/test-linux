#!/bin/bash
set -ex

mkgpt() {
	local disk=${1}

	sudo parted ${disk} mklabel gpt

	sudo parted ${disk} mkpart primary fat32 0 10M --align minimal
	sudo parted ${disk} mkpart logical ext4 10M 20M
	sudo parted ${disk} mkpart extended ext4 20M 30M

	# if use /dev/loop, partition with 'p' suffix
	P=
	if [[ ${disk:0:9} == /dev/loop ]]; then
		P=p
	fi
	sudo mkfs.fat -n TL-TEST ${disk}${P}1
	sudo mkfs.ext4 -T largefile ${disk}${P}2
	sudo mkfs.ext4 -T largefile ${disk}${P}3

	sleep 1
	lsblk -o +fstype,label,uuid
}

sudo parted -ls

BLK=blk.bin

sudo rm -f ${BLK}

sudo dd if=/dev/zero of=${BLK} bs=1M count=310
LOOP=$(sudo losetup --find --show ${BLK})
sudo losetup -j ${BLK}

mkgpt ${LOOP}

sudo losetup --detach ${LOOP}

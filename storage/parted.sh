#!/bin/bash
set -ex

mkgpt() {
	local disk=${1}

	sudo parted ${disk} mklabel gpt

	sudo parted ${disk} mkpart primary ext4 0 10M
	sudo parted ${disk} mkpart logical ext4 10M 20M
	sudo parted ${disk} mkpart extended ext4 20M 30M

	#sudo mkfs.ext4 -T largefile ${disk}1
	#sudo mkfs.ext4 -T largefile ${disk}2
	#sudo mkfs.ext4 -T largefile ${disk}3

	sleep 1
	lsblk -o +fstype,uuid
}

sudo parted -ls

BLK=blk.bin

sudo dd if=/dev/zero of=${BLK} bs=1M count=310
LOOP=$(sudo losetup --find --show ${BLK})
sudo losetup -j ${BLK}

mkgpt ${LOOP}

sudo losetup --detach ${LOOP}

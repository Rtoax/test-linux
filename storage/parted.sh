#!/bin/bash
set -ex

mkgpt() {
	local disk=${1}

	sudo parted ${disk} mklabel gpt

	sudo parted ${disk} mkpart primary fat32 0 64M --align minimal
	sudo parted ${disk} mkpart logical ext4 64M 96M --align minimal
	sudo parted ${disk} mkpart extended ext4 96M 128M --align minimal
	sudo parted ${disk} mkpart extended xfs 128M 512M --align minimal

	# if use /dev/loop, partition with 'p' suffix
	P=
	if [[ ${disk:0:9} == /dev/loop ]]; then
		P=p
	fi
	sudo mkfs.fat -n TL-FAT ${disk}${P}1
	sudo mkfs.ext4 -L TL-EXT4 -T largefile ${disk}${P}2
	sudo mkfs.ext4 -L TL-EXT4 -T largefile ${disk}${P}3
	sudo mkfs.xfs -L TL-XFS ${disk}${P}4

	sleep 1
	lsblk -o +fstype,label,uuid
}

sudo parted -ls

BLK=blk.bin

sudo rm -f ${BLK}

sudo dd if=/dev/zero of=${BLK} bs=1M count=512
LOOP=$(sudo losetup --find --show ${BLK})
sudo losetup -j ${BLK}

goodbye() {
	sudo losetup --detach ${LOOP}
}
trap goodbye EXIT

mkgpt ${LOOP}


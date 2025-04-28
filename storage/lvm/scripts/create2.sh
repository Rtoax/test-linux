#!/bin/bash
set -ex

VG_NAME=$(mktemp -u vg_XXX)
# WARNING: If LV name is too long, df -hT will shows '/dev/dm-N'
LV_NAME=$(uuid)
#LV_NAME=$(mktemp -u lv_XXX)

BIN=$(mktemp -u bin_XXX.dat)
dd if=/dev/zero of=${BIN} bs=1M count=1024

LOOP=$(sudo losetup --find --show ${BIN})

cleanup() {
	sudo umount a.out || :
	sudo rmdir a.out || :
	sudo vgchange -an ${VG_NAME} || :
	sudo losetup --detach ${LOOP} || :
	sudo rm -f ${BIN}
}
trap cleanup EXIT

sudo vgcreate ${VG_NAME} ${LOOP} -y -v
sudo lvcreate -n ${LV_NAME} -L 512M -W y -y ${VG_NAME}

sudo mkfs.xfs /dev/${VG_NAME}/${LV_NAME}
mkdir -p a.out/
sudo mount /dev/${VG_NAME}/${LV_NAME} a.out/

lsblk
df -hT


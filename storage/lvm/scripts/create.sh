#!/bin/bash
set -ex

new_blk()
{
	local name=$1
	dd if=/dev/zero of=${name} bs=1M count=32
	sudo losetup --find --show ${name}
}

# Define variables
DISK1="$(new_blk a.bin)"
DISK2="$(new_blk b.bin)"
VG_NAME="$(mktemp -u vg_name_XXX)"
LV_NAME="$(mktemp -u lv_name_XXX)"
MOUNT_POINT="/mnt/data"

cleanup() {
	sudo umount ${MOUNT_POINT} || :
	sudo lvchange -an ${LV_NAME} || :
	sudo vgchange -an ${VG_NAME} || :
	sudo losetup --detach ${DISK1} || :
	sudo losetup --detach ${DISK2} || :
	sudo rm -rf a.bin b.bin
}
trap cleanup EXIT

# Create Physical Volumes
sudo pvcreate $DISK1 $DISK2

# Create Volume Group
sudo vgcreate $VG_NAME $DISK1 $DISK2

# Create Logical Volume
sudo lvcreate -l 100%FREE -n $LV_NAME $VG_NAME

# Format the Logical Volume
sudo mkfs.ext4 /dev/$VG_NAME/$LV_NAME

# Create Mount Point
sudo mkdir -p $MOUNT_POINT

# Mount the Logical Volume
sudo mount /dev/$VG_NAME/$LV_NAME $MOUNT_POINT

sudo lvs
sudo vgs
sudo pvs
sudo lsblk -o +fstype

# Update /etc/fstab to mount on boot
# echo "/dev/$VG_NAME/$LV_NAME $MOUNT_POINT ext4 defaults 0 0" | sudo tee -a /etc/fstab

echo "LVM setup is complete. Logical Volume is mounted at $MOUNT_POINT."

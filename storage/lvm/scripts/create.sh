#!/bin/bash
set -ex

# Define variables
DISK1="/dev/sdb"
DISK2="/dev/sdc"
VG_NAME="vg_data"
LV_NAME="lv_data"
MOUNT_POINT="/mnt/data"

# Install LVM package
sudo apt-get install -y lvm2 || :
sudo dnf install -y lvm2 || :

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

# Update /etc/fstab to mount on boot
# echo "/dev/$VG_NAME/$LV_NAME $MOUNT_POINT ext4 defaults 0 0" | sudo tee -a /etc/fstab

echo "LVM setup is complete. Logical Volume is mounted at $MOUNT_POINT."

#!/bin/bash

disk=nvme0n1

sudo fdisk -l /dev/${disk} | grep 'Disklabel type'
sudo gdisk -l /dev/${disk} | grep ': present'
sudo parted /dev/${disk} print | grep 'Partition Table:'
sudo udevadm info -q property -n ${disk} | grep ID_PART_TABLE_TYPE

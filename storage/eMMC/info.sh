#!/bin/bash

# Check eMMC version
# =============================================
#   Extended CSD rev 1.8 (MMC 5.1)
sudo mmc extcsd read /dev/mmcblk0 | head -n2

# Max Enhanced Area Size [MAX_ENH_SIZE_MULT]: 0x0009a2
#  i.e. 10100736 KiB
sudo mmc extcsd read /dev/mmcblk0 | grep -A1 MAX_ENH_SIZE_MULT

# Boot partition size [BOOT_SIZE_MULTI: 0x20]
#  128KB * 0x20(32) = 4096KB = 4MB
# See also
#  $ lsblk -o name,fstype,mountpoint,size
#  NAME         FSTYPE MOUNTPOINT      SIZE
#  mmcblk0boot0                          4M
#  mmcblk0boot1                          4M
sudo mmc extcsd read /dev/mmcblk0 | grep BOOT_SIZE_MULTI

# Boot configuration bytes [PARTITION_CONFIG: 0x00]
sudo mmc extcsd read /dev/mmcblk0 | grep PARTITION_CONFIG

# Life time estimation
# The estimation is given in steps of 10% so a value of 0x01 means that
#  0% to 10% life time used.
# This functionality was introduced in eMMC 5.0.
#
# eMMC Life Time Estimation A [EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A]: 0x01
# eMMC Life Time Estimation B [EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B]: 0x00
$ sudo mmc extcsd read /dev/mmcblk0 | grep EXT_CSD_DEVICE_LIFE_TIME_EST

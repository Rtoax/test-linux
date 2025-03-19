#!/bin/bash
set -e

# Create Software RAID
# RAID1: --level 1
# RAID2: --level 2
sudo mdadm --create /dev/md0 -ayes --level 1 --raid-devices 2 /dev/xvd[b,c]1

# show stat
cat /proc/mdstat
# Or
mdadm -D /dev/md0

# Part
sudo mkfs.ext4 /dev/md0

# Se sd faulty in md (Emulate bad disk)
sudo mdadm /dev/md1 -f /dev/sdb5

# Remove disk (after -f)
sudo mdadm /dev/md1 -r /dev/sdb5

# Add new disk
sudo mdadm /dev/md1 -a /dev/sdb7

# Stop RAID
sudo mdadm -S /dev/md1


#!/bin/bash
# refs:
# - https://tthtlc.wordpress.com/2020/01/28/how-to-create-rootfs-filesystem-for-ubuntu-18-04/
set -e

strace=
fstype=ext4

case $1 in
strace) shift; strace=strace; ;;
fstype) shift; fstype=$1; shift; ;;
"") ;;
*) echo >&2 "Unknown $1"; exit 1; ;;
esac

[[ ${strace} ]] && echo "Turn on strace"

sudo dd if=/dev/zero of=fs.${fstype} bs=1M count=4
sudo ${strace} mkfs.${fstype} fs.${fstype}
sudo mkdir -p tmp-mnt
sudo umount tmp-mnt || :
sudo mount fs.${fstype} tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
# add more files or softwares
which tree && sudo tree tmp-mnt/
sudo umount tmp-mnt
sudo rmdir tmp-mnt

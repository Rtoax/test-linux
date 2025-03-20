#!/bin/bash
set -e

strace=""

case $1 in
strace) shift; strace=YES; ;;
*) ;;
esac

[[ ${strace} ]] && echo "Turn on strace"

sudo dd if=/dev/zero of=fs.xfs bs=1M count=310
sudo ${strace:+strace} mkfs.xfs fs.xfs
sudo mkdir -p tmp-mnt
sudo mount fs.xfs tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
sudo tree tmp-mnt/
sudo umount tmp-mnt
sudo rmdir tmp-mnt

sudo xfs_db -c "sb" -c "p" fs.xfs | tr '\n' ';' && echo

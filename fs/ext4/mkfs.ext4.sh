#!/bin/bash
set -e

strace=""

case $1 in
strace) shift; strace=YES; ;;
*) break;
esac

[[ ${strace} ]] && echo "Turn on strace"

sudo dd if=/dev/zero of=fs.ext4 bs=1M count=4
sudo ${strace:+strace} mkfs.ext4 fs.ext4
sudo mkdir -p tmp-mnt
sudo umount tmp-mnt || :
sudo mount fs.ext4 tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
which tree && sudo tree tmp-mnt/
sudo umount tmp-mnt

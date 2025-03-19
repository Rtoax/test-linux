#!/bin/bash
set -e

strace=""

case $1 in
strace) shift; strace=YES; ;;
*) ;;
esac

[[ ${strace} ]] && echo "Turn on strace"

sudo dd if=/dev/zero of=fat.fs bs=1M count=10
sudo ${strace:+strace} mkfs.fat fat.fs
sudo mkdir -p tmp-mnt
sudo mount fat.fs tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
sudo tree tmp-mnt/
sudo umount tmp-mnt


#!/bin/bash

sudo dd if=/dev/zero of=xfs.img bs=4096 count=4096
sudo mkfs.xfs xfs.img
sudo mkdir -p tmp-mnt
sudo mount xfs.img tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
sudo tree tmp-mnt/
sudo umount tmp-mnt

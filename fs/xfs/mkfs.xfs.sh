#!/bin/bash

sudo dd if=/dev/zero of=fs.xfs bs=1M count=310
sudo mkfs.xfs fs.xfs
sudo mkdir -p tmp-mnt
sudo mount fs.xfs tmp-mnt -o loop,rw
sudo cp /etc/os-release tmp-mnt/
sudo tree tmp-mnt/
sudo umount tmp-mnt

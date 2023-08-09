#!/bin/bash 
# 创建 initrd

# 下面命令将创建 ./initramfs.img
sudo mkinitrd ./initramfs.img $(uname -r)

#!/bin/bash

. config

mnt_point=tmp.mnt

sudo dd if=/dev/zero of=sd.img bs=4096 count=4096
sudo mkfs.vfat sd.img
sudo mkdir -p ${mnt_point}
sudo mount sd.img ${mnt_point} -o loop,rw
sudo cp ${BM1684_KERNEL_IMAGE_GZ} ${mnt_point}
sudo umount ${mnt_point}
sudo rmdir ${mnt_point}

sudo chown rongtao:rongtao sd.img

# TODO
/usr/bin/qemu-system-arm \
	-bios ${U_BOOT_DIR}/u-boot.bin \
	-kernel ${U_BOOT_DIR}/u-boot \
	-dtb ${BM1684_DTB} \
	-machine vexpress-a9 \
	-cpu cortex-a9 \
	-sd sd.img

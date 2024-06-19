#!/bin/bash

cp /usr/share/OVMF/OVMF_CODE.fd ovmf.fd

# Pass '-cdrom boot.img' if boot.img only is vfat
qemu-system-x86_64 -m 2048 -drive file=./ovmf.fd,format=raw,if=pflash \
	-drive file=./boot.img,format=raw

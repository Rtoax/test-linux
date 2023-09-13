#!/bin/bash

cp /usr/share/OVMF/OVMF_CODE.fd ovmf.fd
qemu-system-x86_64 -drive file=./ovmf.fd,format=raw,if=pflash -cdrom boot.img

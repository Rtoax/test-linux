#!/bin/bash
set -ex

# qemu-kvm 10.2.92
QEMU_KVM=/home/rongtao/Git/qemu/build/qemu-system-aarch64
#QEMU_KVM=/usr/bin/qemu-system-aarch64

kernel=/boot/vmlinuz-$(uname -r)
initrd=/boot/initrd.img-$(uname -r)
# TODO: stuck
#kernel=/home/rongtao/cxl/vmlinux-6.19.11-200.fc43_cxl.aarch64
#initrd=/home/rongtao/cxl/initramfs-6.19.11-200.fc43_cxl.aarch64.img

# Or: sudo qemu-vm --qemu ${QEMU_KVM} --kernel ${kernel} --initrd ${initrd} --stdio
sudo ${QEMU_KVM} -machine virt -cpu host -accel kvm -m 2G \
	-kernel ${kernel} -initrd ${initrd} \
	-append "earlycon console=ttyAMA0 rdinit=/bin/bash rw" \
	-nographic

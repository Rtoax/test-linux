#!/bin/bash
# Test on:
# 1. NVIDIA DGX Spark
# 2. Kunpeng 920
set -ex

# qemu-kvm 10.2.92, 11.0.92
QEMU_KVM=/home/rongtao/Git/qemu/build/qemu-system-aarch64
#QEMU_KVM=/usr/bin/qemu-system-aarch64

kernel=/boot/vmlinuz-$(uname -r)
initrd=/boot/initrd.img-$(uname -r)
[[ ! -f ${initrd} ]] && initrd=/boot/initramfs-$(uname -r).img

if [[ ! -f ${initrd} ]]; then
	echo >&2 "ERROR: not found initrd in anywhere!"
	exit 1
fi

# TODO: stuck on NVIDIA DGX Spark, Kunpeng 920
#kernel=/home/rongtao/cxl/vmlinux-6.19.11-200.fc43_cxl.aarch64
#initrd=/home/rongtao/cxl/initramfs-6.19.11-200.fc43_cxl.aarch64.img

# TODO: stuck on NVIDIA DGX Spark, Kunpeng 920
#kernel=/home/rongtao/cxl/7.0.0-rc7-00059-g3036cd0d3328/vmlinux-7.0.0-rc7-00059-g3036cd0d3328
#initrd=/home/rongtao/cxl/7.0.0-rc7-00059-g3036cd0d3328/initramfs-7.0.0-rc7-00059-g3036cd0d3328.img

# Or: sudo qemu-vm --qemu ${QEMU_KVM} --kernel ${kernel} --initrd ${initrd} --stdio
sudo ${QEMU_KVM} -name vm-test-aarch64 -machine virt -cpu host -accel kvm -m 2G \
	-kernel ${kernel} -initrd ${initrd} \
	-append "earlycon console=ttyAMA0 rdinit=/bin/bash rw" \
	-nographic

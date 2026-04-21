#!/bin/bash
set -e

qemu() {
	./qemu-vm.sh "${@}"
}

run() {
	qemu --dry-run "${@}"
}

qemu --help
qemu --cxl help
qemu --disk help
qemu --uefi help

run --memory 4GiB --kernel vmlinux
run --name fedora --kernel vmlinuz
run --name fedora --kernel vmlinuz --initrd=initramfs.img --rdinit=/bin/bash --rootfs vm.qcow2

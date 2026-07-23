#!/bin/bash
set -e

qemu() {
	echo -e "\033[1;32m./qemu-vm.sh ${@}\033[m"
	./qemu-vm.sh "${@}"
}

run() {
	qemu --dry-run "${@}"
}

qemu --help
qemu -V --version
qemu --cxl help
qemu --disk help
qemu --uefi help

run --memory 4GiB --kernel vmlinux
run --name fedora --kernel vmlinuz
run --name fedora --kernel vmlinuz --initrd=initramfs.img --rdinit=/bin/bash --rootfs vm.qcow2
run --cpu 10 --kernel vmlinux
run --cpu nr=10 --kernel vmlinux
run --cpu model=base --kernel vmlinux

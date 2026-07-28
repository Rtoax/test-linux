#!/bin/bash
set -e

qemu() {
	echo -e "\033[1;32m./qemu-vm.sh ${@}\033[m"
	./qemu-vm.sh "${@}"
}

run() {
	local name=$(mktemp -u vmname-XXXXX)
	qemu --dry-run --name ${name} --kernel vmlinux "${@}"
}

qemu --help
qemu -V --version
qemu --cxl help
qemu --disk help
qemu --uefi help

run
run --memory 4GiB
run --cpu 10
run --cpu nr=10
run --cpu model=base
run --initrd=initramfs.img --rdinit=/bin/bash --rootfs vm.qcow2

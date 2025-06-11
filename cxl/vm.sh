#!/bin/bash
set -e

sudo dnf install -y cxl-cli

if ! [[ -e initramfs.img ]]; then
	sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		initramfs.img
fi

[[ ! -e vmlinuz ]] && sudo cp /boot/vmlinuz-$(uname -r) vmlinuz

sudo ../init/rootfs/qemu.sh -k vmlinuz -r initramfs.img --initrd --cxl cxl-pmem-4way --stdio "${@}"

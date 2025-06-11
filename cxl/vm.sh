#!/bin/bash
set -e

sudo dnf install -y cxl-cli

sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
	--install 'insmod rmmod modprobe lspci ndctl cxl' \
	--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
	initramfs.img

sudo cp /boot/vmlinuz-$(uname -r) vmlinuz

sudo ../init/rootfs/qemu.sh -k vmlinuz -r initramfs.img --initrd --cxl cxl-pmem --stdio

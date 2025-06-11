#!/bin/bash
# ref: https://github.com/pmem/run_qemu
#
set -e
. /etc/os-release

case ${ID} in
fedora|rhel)
	sudo dnf install -y cxl-cli dracut
	;;
debian|ubuntu)
	sudo apt install -u ndctl dracut
	;;
*)
	echo >&2 "ERROR: not support ${ID}"
	;;
esac

if ! [[ -e initramfs.img ]]; then
	sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl lsblk' \
		--add 'bash systemd kernel-modules fs-lib' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		initramfs.img
fi

[[ ! -e vmlinuz ]] && sudo cp /boot/vmlinuz-$(uname -r) vmlinuz

sudo ../init/rootfs/qemu.sh -k vmlinuz -r initramfs.img --initrd --cxl cxl-pmem-4way-switch --debug --stdio "${@}"

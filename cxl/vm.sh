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

[[ ! -e vmlinuz ]] && sudo cp /boot/vmlinuz-$(uname -r) vmlinuz

if ! [[ -e initramfs.img ]]; then
	sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl lsblk dmidecode tree' \
		--add 'bash systemd kernel-modules fs-lib' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		initramfs.img
fi

if ! [[ -e vm.qcow2 ]]; then
	sudo ../init/rootfs/fedora-arch.sh --rootfs vm.rootfs/ --image vm.qcow2 \
		-i cxl-cli -i cxl-libs -i ndctl \
		-i dmidecode -i kmod -i util-linux -i pciutils \
		-i kernel-$(uname -r) \
		-i kernel-modules-$(uname -r) \
		-i kernel-modules-core-$(uname -r) \
		-i kernel-modules-extra-$(uname -r)
fi

sudo ../init/rootfs/qemu.sh --kernel vmlinuz --initrd initramfs.img --rootfs vm.qcow2 \
	--cxl cxl-vmem-4way --stdio "${@}"

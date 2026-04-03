#!/bin/bash
# ref: https://github.com/pmem/run_qemu
#
set -e
. /etc/os-release

initramfs=${HOME}/cxl/initramfs.img
vmlinuz=${HOME}/cxl/vmlinuz
qcow2=${HOME}/cxl/vm.qcow2

case ${ID} in
fedora|rhel)
	sudo dnf install -y cxl-cli dracut edk2-ovmf
	;;
debian|ubuntu)
	sudo apt install -u ndctl dracut ovmf
	;;
*)
	echo >&2 "ERROR: not support ${ID}"
	;;
esac

[[ ! -e ${vmlinuz} ]] && sudo cp /boot/vmlinuz-$(uname -r) ${vmlinuz}

if ! [[ -e ${initramfs} ]]; then
	sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl lsblk dmidecode tree' \
		--add 'bash systemd kernel-modules fs-lib' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		${initramfs}
fi

if ! [[ -e ${qcow2} ]]; then
	sudo ../scripts/rootfs/fedora.sh --rootfs vm.rootfs/ --image ${qcow2} \
		-i cxl-cli -i cxl-libs -i ndctl -i daxctl \
		-i dmidecode -i kmod -i util-linux -i pciutils \
		-i kernel-$(uname -r) \
		-i kernel-modules-$(uname -r) \
		-i kernel-modules-core-$(uname -r) \
		-i kernel-modules-extra-$(uname -r)
fi

# Mount in guest
# $ sudo mount -t virtiofs Git /mnt
sudo /usr/libexec/virtiofsd --socket-path=/var/run/vhost-fs-git.sock -o source=/home/rongtao/Git/ &

sudo ../scripts/qemu-vm.sh --name vm-test-cxl --memory 4G \
	--kernel ${vmlinuz} --initrd ${initramfs} --rootfs ${qcow2} \
	--virtio-fs-sock=/var/run/vhost-fs-git.sock --virtio-fs-tag Git \
	--cxl cxl-pmem-4way --stdio "${@}"

wait

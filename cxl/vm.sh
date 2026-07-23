#!/bin/bash
# Test CXL devices with Qemu.
#
# Usage: [CUSTOM=1] [NOCXL=1] [DEP=1] [GDB=1] [VIRTIOFS=1] [QEMU=/path/to/qemu-kvm] vm.sh
#
#   DEP=1: install depends first.
#   GDB=1: enable gdb.
#
# Copyright (C) 2025-2026 Rong Tao
#
# Refs:
# - https://github.com/pmem/run_qemu
#
set -e
. /etc/os-release

vmlinuz=${HOME}/cxl/vmlinuz
initramfs=${HOME}/cxl/initramfs.img
rootfs=${HOME}/cxl/vm.qcow2

_dry_run=
for a in ${@}
do
	if [[ " -u --dry --dry-run " =~ " ${a} " ]]; then
		_dry_run=ON
	fi
done

declare -a qargs cxlargs

try_run() {
	if [[ ${_dry_run} ]]; then
		echo -e "DUMP: $ \033[1;32m${@}\033[m"
	else
		eval "${@}"
	fi
}

if [[ ${DEP} ]]; then
	case ${ID} in
	fedora|rhel)
		try_run sudo dnf install -y cxl-cli dracut edk2-ovmf
		;;
	debian|ubuntu)
		try_run sudo apt install -u ndctl dracut ovmf
		;;
	*)
		echo >&2 "ERROR: not support ${ID}"
		;;
	esac
fi

if [[ ! -e ${vmlinuz} ]]; then
	try_run sudo cp /boot/vmlinuz-$(uname -r) ${vmlinuz}
fi

if ! [[ -e ${initramfs} ]]; then
	try_run sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl lsblk dmidecode tree' \
		--add 'bash systemd kernel-modules fs-lib' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		${initramfs}
fi

if ! [[ -e ${rootfs} ]]; then
	try_run sudo rootfs-fedora --rootfs vm.rootfs/ --image ${rootfs} \
		-i cxl-cli -i cxl-libs -i ndctl -i daxctl \
		-i dmidecode -i kmod -i util-linux -i pciutils \
		-i kernel-$(uname -r) \
		-i kernel-modules-$(uname -r) \
		-i kernel-modules-core-$(uname -r) \
		-i kernel-modules-extra-$(uname -r)
fi

# Mount in guest
# $ sudo mount -t virtiofs Pwd /mnt
if [[ ${VIRTIOFS} ]]; then
	try_run sudo /usr/libexec/virtiofsd --socket-path=/var/run/vhost-fs-pwd.sock -o source=$PWD &
	try_run sudo /usr/libexec/virtiofsd --socket-path=/var/run/vhost-fs-git.sock -o source=/home/rongtao/Git/ &

	qargs+=( --virtio-fs-sock=/var/run/vhost-fs-pwd.sock --virtio-fs-tag Pwd )
	qargs+=( --virtio-fs-sock=/var/run/vhost-fs-git.sock --virtio-fs-tag Git )
fi

qargs+=( --name vm-test-cxl )
qargs+=( --memory 8192MiB )
qargs+=( --kernel ${vmlinuz} )
qargs+=( --initrd ${initramfs} )
[[ ${QEMU} ]] && qargs+=( --qemu ${QEMU} )
[[ ${GDB} ]] && qargs+=( --gdb )
qargs+=( --rootfs ${rootfs} )
qargs+=( --stdio )
qargs+=( --monitor )


custom_cxl() {
	cxlargs+=( --cxl pxb=pxb.1 ) # fmw default 0
	cxlargs+=( --cxl pxb=pxb.2,fmw=1 )
	cxlargs+=( --cxl pxb=pxb.3,fmw=1 )
	cxlargs+=( --cxl pxb=pxb.4,fmw=2 )
	cxlargs+=( --cxl pxb=pxb.5,fmw=3 )
	cxlargs+=( --cxl pxb=pxb.6,fmw=4 )

	cxlargs+=( --cxl rp=rp.1,bus=pxb.1,port=1 )
	cxlargs+=( --cxl rp=rp.2,bus=pxb.2,port=1 )
	cxlargs+=( --cxl rp=rp.3,bus=pxb.2,port=1 )
	cxlargs+=( --cxl rp=rp.4,bus=pxb.3,port=1 )

	cxlargs+=( --cxl switch,bus=rp.1,nport=2,portprefix=sw1 )
	cxlargs+=( --cxl switch,bus=rp.2,nport=3,portprefix=sw2 )

	cxlargs+=( --cxl pmem=pmem.1,bus=sw1.1,lsa=pmem.1.lsa,size=2G )
	cxlargs+=( --cxl pmem=pmem.2,bus=sw1.2,lsa=pmem.2.lsa )

	cxlargs+=( --cxl vmem=vmem.1,bus=sw2.1,lsa=vmem.1.lsa )
	cxlargs+=( --cxl vmem=vmem.2,bus=sw2.2 ) # vmem could not set lsa
	cxlargs+=( --cxl vmem=vmem.3,bus=sw2.3,size=2G )
	cxlargs+=( --cxl vmem=vmem.4,bus=rp.3,size=1G )
	cxlargs+=( --cxl vmem=vmem.5,bus=rp.4,size=1G )
}

if [[ ! -z ${CUSTOM} ]]; then
	custom_cxl
else
	cxlargs+=( --cxl device=cxl-pmem-4way )
fi

[[ -z ${NOCXL} ]] && qargs+=( ${cxlargs[@]} )

try_run sudo qemu-vm "${qargs[@]}" "${@}"

wait

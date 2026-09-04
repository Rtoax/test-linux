#!/bin/bash
# Test CXL devices with Qemu.
#
# Usage: [DAEMON=1] [CUSTOM=<type>] [NOCXL=1] [DEP=1] [GDB=1] [VIRTIOFS=1] [QEMU=/path/to/qemu-kvm] vm.sh
#
#   DAEMON=1: running vm in the background
#   CUSTOM=<type>: custom cxl device
#   NOCXL=1: no cxl device
#   DEP=1: install depends first.
#   GDB=1: enable gdb.
#   VIRTIOFS=1: enable virtio-fs filesystem
#   QEMU=: custom qemu process ELF
#
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Refs:
# - https://github.com/pmem/run_qemu
#
set -e
. /etc/os-release

readonly ROOTDIR=${HOME}/cxl
readonly VMLINUX=${ROOTDIR}/vmlinuz
readonly INITRD=${ROOTDIR}/initramfs.img
readonly ROOTFS=${ROOTDIR}/vm.qcow2

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
		exit 1
		;;
	esac
fi

if [[ ! -d ${ROOTDIR} ]]; then
	try_run sudo mkdir ${ROOTDIR}
fi

if [[ ! -e ${VMLINUX} ]]; then
	try_run sudo cp /boot/vmlinuz-$(uname -r) ${VMLINUX}
fi

if ! [[ -e ${INITRD} ]]; then
	try_run sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install '"insmod rmmod modprobe lspci ndctl cxl lsblk dmidecode tree"' \
		--add '"bash systemd kernel-modules fs-lib"' \
		--add-drivers '"cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port"' \
		${INITRD}
fi

if ! [[ -e ${ROOTFS} ]]; then
	try_run sudo rootfs-fedora \
		--rootfs vm.rootfs/ --image ${ROOTFS} \
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

qargs+=( --memory 8192MiB )
qargs+=( --kernel ${VMLINUX} )
qargs+=( --initrd ${INITRD} )
[[ ${QEMU} ]] && qargs+=( --qemu ${QEMU} )
[[ ${GDB} ]] && qargs+=( --gdb )
qargs+=( --rootfs ${ROOTFS},rw )
# When test it on Hygon CPU, console is not easy to use.
if [[ "$(lscpu | grep -wo HygonGenuine)" ]] || [[ ${DAEMON} ]]; then
	qargs+=( --daemon )
else
	qargs+=( --stdio )
fi

custom_cxl_1() {
	# $ qemu-kvm -device pxb-cxl,...
	# see commit b4271dd6068b ("qemu: cxl-pxb: 'lspci -tv'")
	cxlargs+=( --cxl pxb=pxb.1 ) # fmw default 0
	cxlargs+=( --cxl pxb=pxb.2,fmw=1 )
	cxlargs+=( --cxl pxb=pxb.3,fmw=2 )
	cxlargs+=( --cxl pxb=pxb.4,fixed-memory-window=3 )
	cxlargs+=( --cxl pxb=pxb.5,fixed-memory-window=4 )
	cxlargs+=( --cxl pxb=pxb.6,fixed-memory-window=5 )

	# $ qemu-kvm -device cxl-rp,...
	# see commit f6f541dae696 ("qemu: cxl-rp(root-port): 'lspci -tv'")
	cxlargs+=( --cxl rp=rp.1,bus=pxb.1,port=1 )
	cxlargs+=( --cxl rp=rp.2,bus=pxb.2,port=1 )
	cxlargs+=( --cxl root-port=rp.3,bus=pxb.3,port=1 )
	cxlargs+=( --cxl root-port=rp.4,bus=pxb.4,port=1 )

	# $ qemu-kvm -device cxl-upstream,... -device cxl-downstream,...
	# see commit 559bfebf5d44 ("qemu: cxl-switch: 'lspci -tv'")
	cxlargs+=( --cxl switch,bus=rp.1,nport=4,portprefix=sw1 )
	cxlargs+=( --cxl switch,bus=rp.2,nport=4,portprefix=sw2 )
	cxlargs+=( --cxl switch,bus=rp.3,nport=4,portprefix=sw3 )
	cxlargs+=( --cxl switch,bus=rp.4,nport=4,portprefix=sw4 )

	# $ qemu-kvm -device cxl-type3,...,persistent-memdev=...
	# see commit 445c8c03b035 ("qemu: cxl-type3: persistent-memdev: lspci, acpi")
	cxlargs+=( --cxl pmem=pmem.1,bus=sw1.1,lsa=pmem.1.lsa,size=2G )
	cxlargs+=( --cxl pmem=pmem.2,bus=sw1.2,lsa=pmem.2.lsa,size=2G )
	cxlargs+=( --cxl pmem=pmem.3,bus=sw1.3,lsa=pmem.3.lsa,size=2G )
	cxlargs+=( --cxl pmem=pmem.4,bus=sw1.4,lsa=pmem.4.lsa,size=2G )

	# $ qemu-kvm -device cxl-type3,...,volatile-memdev=...
	cxlargs+=( --cxl vmem=vmem.1,bus=sw2.1,lsa=vmem.1.lsa )
	cxlargs+=( --cxl vmem=vmem.2,bus=sw2.2 ) # vmem could not set lsa
	cxlargs+=( --cxl vmem=vmem.3,bus=sw2.3,size=2G )
	cxlargs+=( --cxl vmem=vmem.4,bus=sw2.4,size=2G )

	# Dynamic capacity vmem device could not see "ram_size" in 'cxl list'.
	cxlargs+=( --cxl vmem=vmem.5,bus=sw3.1,lsa=vmem.5.lsa,dc )
	cxlargs+=( --cxl vmem=vmem.6,bus=sw3.2,dc ) # vmem could not set lsa
	cxlargs+=( --cxl vmem=vmem.7,bus=sw3.3,size=2G,dynamic-capacity )
	cxlargs+=( --cxl vmem=vmem.8,bus=sw3.4,size=2G,dynamic-capacity )
}

# ref https://docs.kernel.org/driver-api/cxl/linux/cxl-driver.html
custom_cxl_2() {
	cxlargs+=( --cxl pxb=pxb.1 )
	cxlargs+=( --cxl pxb=pxb.2 )
	cxlargs+=( --cxl pxb=pxb.3 )
	cxlargs+=( --cxl pxb=pxb.4 )

	cxlargs+=( --cxl rp=rp.1,bus=pxb.1,port=1 )
	cxlargs+=( --cxl rp=rp.2,bus=pxb.2,port=1 )

	cxlargs+=( --cxl vmem=vmem.1,bus=rp.1,lsa=vmem.1.lsa )
	cxlargs+=( --cxl vmem=vmem.2,bus=rp.2,lsa=vmem.2.lsa )
}

case ${CUSTOM} in
1)
	custom_cxl_1
	;;
2)
	custom_cxl_2
	;;
"")
	CUSTOM=cxl-vmem-4way
	cxlargs+=( --cxl device=${CUSTOM} )
	;;
*)
	cxlargs+=( --cxl device=${CUSTOM} )
	;;
esac

[[ -z ${NOCXL} ]] && qargs+=( ${cxlargs[@]} )

qargs+=( --name cxl-${CUSTOM:+custom-${CUSTOM}-}$(mktemp -u XXXX) )

try_run sudo qemu-vm "${qargs[@]}" "${@}"

wait

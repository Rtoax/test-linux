#!/bin/bash
set -e

. ../../libs/qemu.sh

qemu=$(get_qemu_kvm_emulator)
kernel=$1
rootfs=$2

usage() {
	echo -e "qemu.sh [kernel] [rootfs]"
}

[[ -z ${kernel} ]] && usage && exit 1

kernel=$(realpath ${kernel})
rootfs=$(realpath ${rootfs})

set -x
${qemu} -name vm-test-rootfs -uuid $(uuid) \
	-qmp unix:$PWD/qmp.sock,server=on,wait=off \
	-m 2048M,slots=10,maxmem=129139M \
	-initrd ${rootfs} \
	-kernel ${kernel} -append root=${rootfs}

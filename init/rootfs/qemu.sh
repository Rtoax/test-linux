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

declare -a qemu_args kernel_args

if [[ ${STDIO} ]]; then
	qemu_args+=( -serial mon:stdio -nographic )
	kernel_args+=( rw console=ttyS0 )
fi

set -x
${qemu} -name vm-test-rootfs -uuid $(uuid) \
	-qmp unix:$PWD/qmp.sock,server=on,wait=off \
	-m 2048M,slots=10,maxmem=129139M \
	-drive file=${rootfs},format=raw,if=virtio \
	${qemu_args[@]} \
	-kernel ${kernel} -append "root=/dev/vda ${kernel_args[@]}"

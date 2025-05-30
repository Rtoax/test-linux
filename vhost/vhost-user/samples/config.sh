#!/bin/bash
set -e
. ../../qemu/libqemu.sh

QEMU=$(get_qemu_kvm_emulator)
IMG_QCOW2=$PWD/vm.qcow2
SOCK_VHOST_PATH=$PWD/vhost.sock

[[ -z ${QEMU} ]] && echo "Not found Qemu/kvm emulator" && exit 1

if [[ ! -e ${IMG_QCOW2} ]]; then
	qemu-img create -f qcow2 ${IMG_QCOW2} 10G
fi

#!/bin/bash
set -e

readonly ROOTDIR=${HOME}/cxl
readonly VMLINUX=${ROOTDIR}/vmlinuz

vm() {
	./vm.sh -u "${@}"
}

if [[ ! -e ${VMLINUX} ]]; then
	exit 0
fi

vm
DEP=1 vm
DAEMON=1 vm
CUSTOM=1 vm
GDB=1 vm
VIRTIOFS=1 vm
QEMU=/usr/bin/ls vm

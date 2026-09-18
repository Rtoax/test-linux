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
GRAPHIC=1 vm
DAEMON=1 vm
for custom in 1 2 3 multi-level-switch 4 big-vmem help "?"
do
	CUSTOM=${custom} vm
done
GDB=1 vm
VIRTIOFS=1 vm
QEMU=/usr/bin/ls vm
DEP=1 DAEMON=1 CUSTOM=1 GDB=1 VIRTIOFS=1 QEMU=/usr/bin/ls vm

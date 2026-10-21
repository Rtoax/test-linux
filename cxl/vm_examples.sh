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
for dev in 1 complex 2 3 multi-level-switch 4 big-vmem help "?"
do
	CUSTOM=${dev} vm
	CXLDEV=${dev} vm
	CUSTOM=${dev} CXLDEV=${dev} vm
done
GDB=1 vm
VIRTIOFS=1 vm
QEMU=/usr/bin/ls vm
DEP=1 DAEMON=1 CUSTOM=1 GDB=1 VIRTIOFS=1 QEMU=/usr/bin/ls vm

if CUSTOM=1 CXLDEV=2 vm; then
	echo >&2 "ERROR: If CUSTOM!=CXLDEV, an error should be report!!!!"
	exit 1
fi

echo DONE

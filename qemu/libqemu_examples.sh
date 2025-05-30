#!/bin/bash
set -e

. libqemu.sh

echo $(get_qemu_kvm_emulator)
qemu=$(get_qemu_kvm_emulator_arch $(uname -m)) || {
	echo "ERROR: I know you may run failed." >&2
	exit 1
}
echo ${qemu}

#!/bin/bash

. qemu.sh

echo $(get_qemu_kvm_emulator)
qemu=$(get_qemu_kvm_emulator_arch $(uname -m)) || {
	echo "I know you could run faild."
}

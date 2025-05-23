#!/bin/bash

. ../qemu/qemu.sh

emulator=$(get_qemu_kvm_emulator)

${emulator} -M virt -cpu help

allflags=( $(${emulator} -enable-kvm -cpu help | \
	awk '/flags/ {y=1; getline}; y {print}' | \
	tr ' ' '\n' | grep -Ev "^$" | \
	sed -r 's|^|+|' | tr '\n' ',' | sed -r "s|,$||") )

echo Flags: ${allflags}

# warning: host doesn't support requested feature: CPUID.07H:EBX.intel-pt [bit 25]
# ${emulator} -enable-kvm -cpu "base,check,${allflags}"

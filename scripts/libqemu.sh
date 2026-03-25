#!/bin/bash
set -e

find_qemu_emulator()
{
	local qemu_kvm=""
	local emulators=( "$@" )

	for b in ${emulators[@]}
	do
		if [[ -e ${b} ]]; then
			qemu_kvm=${b}
			break
		fi
	done

	if [[ -z $qemu_kvm ]]; then
		echo "ERROR: Not found qemu-kvm emulator" >&2
		exit 1
	else
		echo $qemu_kvm
	fi
}

get_qemu_kvm_emulator()
{
	local qemu_kvm_possible_emulators=(
		/usr/libexec/qemu-kvm
		/usr/libexec/qemu-system-$(uname -m)
		/usr/bin/qemu-system-$(uname -m)
		/usr/local/bin/qemu-system-$(uname -m)
	)

	find_qemu_emulator ${qemu_kvm_possible_emulators[@]}
	return 0
}

get_qemu_kvm_emulator_arch()
{
	local arch=$1
	if [[ -z ${arch} ]]; then
		echo "ERROR: Must specify arch" >&2
		exit 1
	fi
	local qemu_kvm_possible_emulators=(
		/usr/libexec/qemu-system-${arch}
		/usr/bin/qemu-system-${arch}
		/usr/local/bin/qemu-system-${arch}
	)

	find_qemu_emulator ${qemu_kvm_possible_emulators[@]}
	return 0
}

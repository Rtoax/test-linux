#!/bin/bash
readonly LIBQEMU_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBQEMU_ROOT}/liblog.sh

find_qemu_emulator()
{
	local qemu_kvm
	local emulators=( "$@" )

	for b in ${emulators[@]}
	do
		if [[ -e ${b} ]]; then
			qemu_kvm=${b}
			break
		fi
	done

	if [[ -z $qemu_kvm ]]; then
		error "Not found qemu-kvm emulator"
	else
		echo $qemu_kvm
	fi
}

# $1: specify cpu architecture, like: aarch64
get_qemu_kvm_emulator_arch()
{
	local arch=$1
	if [[ -z ${arch} ]]; then
		error "Must specify arch" >&2
	fi

	local emulators=(
		/home/rongtao/Git/qemu/build/qemu-system-${arch}
		/usr/libexec/qemu-system-${arch}
		/usr/bin/qemu-system-${arch}
		/usr/local/bin/qemu-system-${arch}
	)

	if [[ $(uname -m) == ${arch} ]]; then
		emulators+=( /usr/libexec/qemu-kvm )
	fi

	find_qemu_emulator ${emulators[@]}
	return 0
}

get_qemu_kvm_emulator()
{
	get_qemu_kvm_emulator_arch $(uname -m)
	return 0
}

#!/bin/bash
set -ex

declare -a args

. ../../../qemu/libqemu.sh

qemu_emulator=$(get_qemu_kvm_emulator)

cp /usr/share/OVMF/OVMF_CODE.fd ovmf.fd

if [[ $(uname -m) == aarch64 ]]; then
	args+=( -machine virt )
	# Try to fix: device requires 67108864 bytes, block backend provides 1966080 bytes
	truncate --size=64M ovmf.fd
fi

# Pass '-cdrom boot.img' if boot.img only is vfat
${qemu_emulator} ${args[@]} \
	-m 2048 -drive file=./ovmf.fd,format=raw,if=pflash \
	-drive file=./boot.img,format=raw

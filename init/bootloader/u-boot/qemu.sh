#!/bin/bash

. compile.sh
. ../../../libs/qemu.sh

program_name=$0
qemu_emulator=$(get_qemu_kvm_emulator)
U_BOOT_DIR=/home/rongtao/Git/u-boot

ub_qemu_x86_64_easy()
{
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.rom
}

ub_qemu_x86_64_complex()
{
	local root_img=${PWD}/root.img
	local iso_img=/home/isos/ubuntu-22.04-desktop-amd64.iso

	qemu-img create -f raw ${root_img} 10G
	${qemu_emulator} -m 8G -smp 4 -bios ${U_BOOT_DIR}/u-boot.rom \
		-drive file=${root_img},if=virtio,driver=raw \
		-drive file=${iso_img},if=virtio,driver=raw
}

ub_qemu_x86_64_custom()
{
	# kill: pkill ${qemu_emulator} -f
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.rom \
		-machine acpi=on \
		-device sdhci-pci \
			-device sd-card,drive=mydrive \
			-drive id=mydrive,if=none,format=qcow2,file=${PWD}/test.qcow2 \
		-m 8G -smp 4
}

ub_qemu_aarch64_custom()
{
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.bin \
		-kernel ${U_BOOT_DIR}/u-boot \
		-machine virt -cpu cortex-a57
}

compile_uboot()
{
	pushd ${U_BOOT_DIR}
	if [[ $(uname -m) == x86_64 ]] && [[ $arch_type == x86_64 ]]; then
		compile_qemu_x86_64
	elif [[ $(uname -m) == aarch64 ]] && [[ $arch_type == aarch64 ]]; then
		compile_qemu_aarch64
	elif [[ $(uname -m) == x86_64 ]] && [[ $arch_type == aarch64 ]]; then
		compile_cross_aarch64
	fi
	popd
}

usage()
{
	cat <<-EOF
	test u-boot with qemu:

	-c, --cross          cross compile, chose another arch.
	-r, --run            set run type: complex, easy, custom
	                     default: ${run_type}
	-u, --uboot          re-compile u-boot

	-v, --verbose
	-h, --help

	# Running $(uname -m) qemu U-Boot with re-compile u-boot
	$ ${program_name} --uboot

	# Running cross-compiled U-Boot with re-compile u-boot
	$ ${program_name} --uboot --cross
	EOF
}

arch_type=$(uname -m)
run_type=custom

while true
do
case $1 in
-c | --cross)
	shift
	if [[ $arch_type == x86_64 ]]; then
		arch_type=aarch64
	elif [[ $arch_type == aarch64 ]]; then
		arch_type=x86_64
	fi
	qemu_emulator=$(get_qemu_kvm_emulator_arch ${arch_type})
	;;
-v | --verbose)
	shift
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
	;;
-h | --help)
	shift
	usage
	exit 0
	;;
-u | --uboot)
	shift
	compile_uboot
	;;
-r | --run)
	shift
	run_type=$1
	shift
	;;
*)
	break
	;;
esac
done

case $run_type in
complex)
	ub_qemu_${arch_type}_complex
	;;
easy)
	ub_qemu_${arch_type}_easy
	;;
custom)
	ub_qemu_${arch_type}_custom
	;;
*)
	usage
	echo "ERROR: Unkown run type"
	exit 1
	;;
esac

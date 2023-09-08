#!/bin/bash

. ../../../libs/qemu.sh
. config

program_name=$0
qemu_emulator=

arch_type=$(uname -m)
run_type=custom
cross_run=

function update_qemu_kvm() {
	if [[ ${arch_type} == $(uname -m) ]]; then
		qemu_emulator=$(get_qemu_kvm_emulator)
	else
		qemu_emulator=$(get_qemu_kvm_emulator_arch ${arch_type})
	fi
}

ub_qemu_easy() {
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.rom
}

# TODO
ub_qemu_complex()
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
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.rom \
		-machine q35,acpi=on \
		-device sdhci-pci \
			-device sd-card,drive=mydrive \
			-drive id=mydrive,if=none,format=qcow2,file=${PWD}/test.qcow2 \
		-m 2G -smp cores=4
}

ub_qemu_aarch64_custom()
{
	local args

	# https://github.com/ARM-software/u-boot/blob/master/doc/README.qemu-arm
	args+=( -machine virt -cpu cortex-a57 )
	args+=( -bios ${U_BOOT_DIR}/u-boot.bin )

	# FIXME: Pass different device tree blob
	#args+=( -dtb ${U_BOOT_DIR}/arch/arm/dts/rk3399-nanopc-t4.dtb )

	${qemu_emulator} -nographic \
		-kernel ${U_BOOT_DIR}/u-boot \
		-device sdhci-pci,sd-spec-version=3 \
			-drive if=none,file=uboot.disk,format=raw,id=MMC1 \
			-device sd-card,drive=MMC1 \
		${args[@]}
}

ub_qemu_arm_custom()
{
	orangepi() {
		${qemu_emulator} -machine orangepi-pc -nographic -nic user \
			-kernel ${U_BOOT_DIR}/u-boot \
			-dtb ${LINUX_KERNEL_DIR}/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb \
			-sd uboot.disk \
			-m 1G -smp 4
	}

	# Ref: https://juejin.cn/post/6844903606500458510
	# '-sd uboot.disk' as same as '-drive if=sd,driver=file,filename=uboot.disk'
	vexpress_ca9x4() {
		${qemu_emulator} -machine vexpress-a9 -nographic -m 512M \
			-kernel ${U_BOOT_DIR}/u-boot \
			-dtb ${U_BOOT_DIR}/arch/arm/dts/vexpress-v2p-ca9.dtb \
			-drive if=sd,driver=file,filename=uboot.disk
	}
	vexpress_ca9x4
}

usage()
{
	cat <<-EOF
	test u-boot with qemu:

	-a, --arch           specify arch: x86_64, aarch64, arm
	-r, --run            run type: easy, custom, complex
	-v, --verbose
	-h, --help
	EOF
}

while true
do
case $1 in
-a | --arch)
	shift
	arch_type=$1
	shift
	;;
-r | --run)
	shift
	run_type=$1
	shift
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
-*)
	usage
	echo "ERROR: Unkown $1"
	exit 1
	;;
*)
	break
	;;
esac
done

update_qemu_kvm

case $run_type in
complex)
	ub_qemu_complex
	;;
easy)
	ub_qemu_easy
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

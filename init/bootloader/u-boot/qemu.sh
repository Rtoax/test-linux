#!/bin/bash

. ../../../libs/qemu.sh
. config

program_name=$0
qemu_emulator=

arch_type=$(uname -m)

dumpcmd=

declare -a qemu_args


qemu_eval()
{
	if [[ -z $dumpcmd ]]; then
		eval "$@"
	else
		echo -e "\033[1;33mDUMPCMD\033[m: $@"
	fi
}

################################################################################
# Emulate Disk
# ref: https://u-boot.readthedocs.io/en/latest/board/emulation/blkdev.html
add_emmc_disk() {
	qemu_args+=( -device sdhci-pci,sd-spec-version=3 )
	qemu_args+=(		-drive if=none,file=uboot.disk,format=raw,id=MMC1 )
	qemu_args+=(		-device sd-card,drive=MMC1 )
}
add_nvme_disk() {
	local disk_type=$1
	local drive_id=$2
	local disk_path=$3
	qemu_args+=( -drive if=none,file=${disk_path},format=${disk_type},id=${drive_id} )
	qemu_args+=(		-device nvme,drive=${drive_id},serial=sn-${drive_id} )
}
add_sata_disk() {
	qemu_args+=( -device ahci,id=ahci0 )
	qemu_args+=(		-drive if=none,file=uboot.disk,format=raw,id=SATA1 )
	qemu_args+=(		-device ide-hd,bus=ahci0.0,drive=SATA1 )
}
add_virtio_disk() {
	qemu_args+=(	-drive if=none,file=uboot.disk,format=raw,id=VIRTIO1 )
	qemu_args+=(		-device virtio-blk,drive=VIRTIO1 )
}

# TODO: Mount an ISO
add_cdrom_and_install() {
	qemu_args+=( -cdrom ${CCLINUX_ISO_AARCH64} )

	local qcow2=$(mktemp --dry-run test-XXXXXX.qcow2)

	qemu_eval qemu-img create -f qcow2 ${qcow2} 100G
	add_nvme_disk qcow2 NVME2 ${qcow2}
}

################################################################################
# Just an example, never run
ub_qemu_easy() {
	${qemu_emulator} -nographic -bios ${U_BOOT_DIR}/u-boot.rom
}

# Just an example, never run
ub_qemu_complex() {
	local root_img=${PWD}/root.img
	local iso_img=/home/isos/ubuntu-22.04-desktop-amd64.iso

	qemu-img create -f raw ${root_img} 10G
	${qemu_emulator} -m 8G -smp 4 -bios ${U_BOOT_DIR}/u-boot.rom \
		-drive file=${root_img},if=virtio,driver=raw \
		-drive file=${iso_img},if=virtio,driver=raw
}

################################################################################
ub_qemu_x86_64_custom()
{
	qemu_args+=( -nographic )
	qemu_args+=( -machine q35,acpi=on )
	qemu_args+=( -bios ${U_BOOT_DIR}/u-boot.rom )
	qemu_args+=( -m 2G -smp cores=4 )

	add_nvme_disk qcow2 NVME1 test.qcow2
}

################################################################################
ub_qemu_aarch64_custom()
{
	# https://github.com/ARM-software/u-boot/blob/master/doc/README.qemu-arm
	qemu_args+=( -nographic )
	qemu_args+=( -kernel ${U_BOOT_DIR}/u-boot )
	qemu_args+=( -machine virt -cpu cortex-a57 )
	qemu_args+=( -bios ${U_BOOT_DIR}/u-boot.bin )
	qemu_args+=( -m 2048M )

	# FIXME: Pass different device tree blob
	#qemu_args+=( -dtb ${U_BOOT_DIR}/arch/arm/dts/rk3399-nanopc-t4.dtb )

	add_nvme_disk raw NVME1 uboot.disk

	add_cdrom_and_install
}

################################################################################
ub_qemu_arm_custom()
{
	orangepi() {
		qemu_args+=( -machine orangepi-pc -nographic -nic user )
		qemu_args+=( -kernel ${U_BOOT_DIR}/u-boot )
		qemu_args+=( -dtb ${LINUX_KERNEL_DIR}/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb )
		qemu_args+=( -sd uboot.disk )
		qemu_args+=( -m 1G -smp 4 )
	}

	# Ref: https://juejin.cn/post/6844903606500458510
	# '-sd uboot.disk' as same as '-drive if=sd,driver=file,filename=uboot.disk'
	vexpress_ca9x4() {
		qemu_args+=( -machine vexpress-a9 )
		qemu_args+=( -nographic -m 512M )
		qemu_args+=( -kernel ${U_BOOT_DIR}/u-boot )
		qemu_args+=( -dtb ${U_BOOT_DIR}/arch/arm/dts/vexpress-v2p-ca9.dtb )
		qemu_args+=( -drive if=sd,driver=file,filename=uboot.disk )
	}
	vexpress_ca9x4
}

################################################################################
usage()
{
	echo "
test u-boot with qemu:

-a, --arch           specify arch: x86_64, aarch64, arm

-d, --dumpcmd        dump command instead of execute
-v, --verbose
-h, --help
"
}

################################################################################
while true
do
case $1 in
-a | --arch)
	shift
	arch_type=$1
	shift
	;;
-d | --dumpcmd)
	shift
	dumpcmd=YES
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

if [[ ${arch_type} == $(uname -m) ]]; then
	qemu_emulator=$(get_qemu_kvm_emulator)
else
	qemu_emulator=$(get_qemu_kvm_emulator_arch ${arch_type})
fi
qemu_emulator="qemu_eval "${qemu_emulator}

ub_qemu_${arch_type}_custom

${qemu_emulator} ${qemu_args[@]}

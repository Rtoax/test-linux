#!/bin/bash
set -e

. ../../qemu/libqemu.sh
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

check_file()
{
	local f=$1
	if [[ ! -e ${f} ]]; then
		echo "ERROR: ${f} is not exist"
		exit 1
	fi
}

################################################################################
# Emulate Disk
# ref: https://u-boot.readthedocs.io/en/latest/board/emulation/blkdev.html
add_emmc_disk() {
	check_file uboot.disk

	qemu_args+=( -device sdhci-pci,sd-spec-version=3 )
	qemu_args+=(		-drive if=none,file=uboot.disk,format=raw,id=MMC1 )
	qemu_args+=(		-device sd-card,drive=MMC1 )
}
add_nvme_disk() {
	local disk_type=$1
	local disk_path=$2
	local drive_id=$(mktemp --dry-run NVME-XXXXXX)

	check_file ${disk_path}

	qemu_args+=( -drive if=none,file=${disk_path},format=${disk_type},id=${drive_id} )
	qemu_args+=(		-device nvme,drive=${drive_id},serial=sn-${drive_id} )
}
add_sata_disk() {
	check_file uboot.disk

	qemu_args+=( -device ahci,id=ahci0 )
	qemu_args+=(		-drive if=none,file=uboot.disk,format=raw,id=SATA1 )
	qemu_args+=(		-device ide-hd,bus=ahci0.0,drive=SATA1 )
}
add_virtio_disk() {
	check_file uboot.disk

	qemu_args+=(	-drive if=none,file=uboot.disk,format=raw,id=VIRTIO1 )
	qemu_args+=(		-device virtio-blk,drive=VIRTIO1 )
}

create_nvme() {
	local qcow2=$(mktemp --dry-run test-XXXXXX.qcow2)
	qemu_eval qemu-img create -f qcow2 ${qcow2} 100G
	add_nvme_disk qcow2 ${qcow2}
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
	check_file ${U_BOOT_DIR}/u-boot.rom

	qemu_args+=( -machine q35,acpi=on )
	qemu_args+=( -bios ${U_BOOT_DIR}/u-boot.rom )
	qemu_args+=( -m 2G -smp cores=4 )

	add_nvme_disk qcow2 test.qcow2
}

################################################################################
ub_qemu_aarch64_custom()
{
	check_file ${U_BOOT_DIR}/u-boot.bin

	# https://github.com/ARM-software/u-boot/blob/master/doc/README.qemu-arm
	qemu_args+=( -machine virt -cpu cortex-a57 )
	qemu_args+=( -bios ${U_BOOT_DIR}/u-boot.bin )
	qemu_args+=( -m 2048M )

	# FIXME: Pass different device tree blob
	#qemu_args+=( -dtb ${U_BOOT_DIR}/arch/arm/dts/rk3399-nanopc-t4.dtb )
}

################################################################################
ub_qemu_arm_custom()
{
	orangepi() {
		qemu_args+=( -machine orangepi-pc -nic user )
		qemu_args+=( -kernel ${U_BOOT_DIR}/u-boot )
		qemu_args+=( -dtb ${LINUX_KERNEL_DIR}/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb )
		qemu_args+=( -sd uboot.disk )
		qemu_args+=( -m 1G -smp 4 )
	}

	# Ref: https://juejin.cn/post/6844903606500458510
	# '-sd uboot.disk' as same as '-drive if=sd,driver=file,filename=uboot.disk'
	vexpress_ca9x4() {
		qemu_args+=( -machine vexpress-a9 )
		qemu_args+=( -m 512M )
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

  -u, --uboot-dir [directory]
                       default: ${U_BOOT_DIR}

  --nvme               add qcow2 as NVMe storage (may be listed multiple times)
  --graphic            with graphic
  -d, --dumpcmd        dump command instead of execute
  -v, --verbose
  -h, --help

examples:

  # Dump command
  $ ./qemu.sh -a aarch64 -d
  # Add nvme storage and an ISO
  $ ./qemu.sh -a aarch64 --nvme test.qcow2 --cdrom ${OS_ISO_AARCH64}
  # Above will generate test-03PP38.qcow2, then:
  $ ./qemu.sh -a aarch64 --nvme test-03PP38.qcow2
"
	exit ${1-0}
}

################################################################################
graphic=
declare -a nvmes

TEMP=$(getopt \
	--options a:du:v:h \
	--long arch: \
	--long nvme: \
	--long uboot-dir: \
	--long cdrom: \
	--long graphic \
	--long dumpcmd \
	--long verbose: \
	--long help \
	-n ${program_name} -- "$@")

test $? != 0 && usage 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-a | --arch)
		shift
		arch_type=$1
		shift
		;;
	--nvme)
		shift
		if [[ ! -e ${1} ]]; then
			echo "ERROR: ${1} is not exist."
			exit 1
		fi
		nvmes+=( $1 )
		shift
		;;
	-u | --uboot-dir)
		shift
		U_BOOT_DIR=$1
		if [[ ! -d ${U_BOOT_DIR} ]]; then
			echo "ERROR: ${U_BOOT_DIR} is not directory"
			exit 1
		fi
		shift
		;;
	--cdrom)
		shift
		if [[ ! -e ${1} ]]; then
			echo "ERROR: ${1} is not exist."
			exit 1
		fi
		qemu_args+=( -cdrom ${1} )
		# If specify ISO, need a target storage
		create_nvme
		shift
		;;
	--graphic)
		shift
		graphic=YES
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
		usage 0
		;;
	--)
		shift
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

[[ -z ${graphic} ]] && qemu_args+=( -nographic )

for nvme in ${nvmes[@]}
do
	add_nvme_disk qcow2 ${nvme}
done

ub_qemu_${arch_type}_custom

${qemu_emulator} ${qemu_args[@]}

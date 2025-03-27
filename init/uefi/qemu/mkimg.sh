#!/bin/bash
set -e

readonly prog=uefi-mkimg

source /etc/os-release

BOOTFLOW=3
readonly BOOTFLOW_NUM="1 2 3"
IMG_NAME=boot.img

EFI_ARCH=
IMG_BOOTEFI=
# The file name is not case sensitive.
readonly IMG_BOOTEFI_AA64=BOOTAA64.EFI
readonly IMG_BOOTEFI_X64=BOOTX64.EFI

IMG_BOOTCSV=
readonly IMG_BOOTCSV_AA64=BOOTAA64.CSV
readonly IMG_BOOTCSV_X64=BOOTX64.CSV

VENDOR_ID=
DEV_LOOP=

MNT_BOOT=mnt.boot
MNT_BOOT_EFI=mnt.boot.efi

case $(uname -m) in
aarch64)
	EFI_ARCH=aa64
	IMG_BOOTEFI=${IMG_BOOTEFI_AA64}
	IMG_BOOTCSV=${IMG_BOOTCSV_AA64}
	;;
x86_64)
	EFI_ARCH=x64
	IMG_BOOTEFI=${IMG_BOOTEFI_X64}
	IMG_BOOTCSV=${IMG_BOOTCSV_X64}
	;;
*)
	echo "ERROR: Unknown arch $(uname -m)"
	exit 1
	;;
esac

__usage__()
{
	echo -e "
${prog} [-n=name] [-b=NUM] [-V=vendor] [-h|--help]

-n, --name [IMG]   specify boot image name, default: ${IMG_NAME}

-V, --vendor [NAME] specify verdor, like fedora, ubuntu, default: ${ID}

-b, --bootflow [N] specify bootflow of uefi/shim/grub, support: ${BOOTFLOW_NUM}
                   1: UEFI load grub2 directly
                   2: UEFI load ${IMG_BOOTEFI} -> grub2
                   3: UEFI load ${IMG_BOOTEFI} -> fb${EFI_ARCH}.efi(${IMG_BOOTCSV}) -> shim${EFI_ARCH}.efi -> grub2

-h, --help         show this help information
-v, --verbose      show detail during running
" | more

	exit ${1-0}
}

# __main__
GETOPT_ARGS=$(getopt \
	--options n:b:V:hv \
	--long name: \
	--long vendor: \
	--long bootflow: \
	--long help \
	--long verbose \
	-n ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$GETOPT_ARGS"

while true; do
	case $1 in
	-n|--name)
		shift
		IMG_NAME=$1
		shift
		;;
	-V|--vendor)
		shift
		VENDOR_ID=$1
		shift
		;;
	-b|--bootflow)
		shift
		BOOTFLOW=$1
		if ! [[ " ${BOOTFLOW_NUM} " =~ " ${BOOTFLOW} " ]]; then
			echo >&2 "ERROR: bootflow only support ${BOOTFLOW_NUM}"
			exit 1
		fi
		shift
		;;
	-h|--help)
		shift
		__usage__
		;;
	-v|--verbose)
		shift
		verbose=YES
		set -x
		;;
	--)
		shift
		break
		;;
	esac
done

[[ -z ${VENDOR_ID} ]] && VENDOR_ID=${ID}

dd if=/dev/zero of=${IMG_NAME} bs=1M count=512

# Pass -drive file=./${IMG_NAME},format=raw to qemu
mk_multi_partitions_with_fdisk()
{
	local fdisk_script=fdisk.txt
	# g: Created a new GPT disklabel
	# n: add a new partition
	# 1: partition number 1
	# 2048: First sector
	# +100M: Last sector
	# t: change a partition type
	# 1: Changed type of partition 'Linux filesystem' to 'EFI System'
	# n: add a new partition
	# 2: partition number 2
	# ' ': use default First sector
	# ' ': use default Last sector
	# w: write table to disk and exit
	cat>${fdisk_script}<<-EOF
	g
	n
	1
	2048
	+100M
	t
	1
	n
	2


	w
	EOF
	DEV_LOOP=$( sudo losetup --find --show ${IMG_NAME} )

	# FIXME: fdisk return 1, the error/warning:
	# Re-reading the partition table failed.: Invalid argument
	# The kernel still uses the old table. The new table will be used at
	# the next reboot or after you run partprobe(8) or partx(8).
	sudo fdisk ${DEV_LOOP} < ${fdisk_script} || true

	sudo losetup --detach ${DEV_LOOP}

	DEV_LOOP=$( sudo losetup --find --partscan --show ${IMG_NAME} )

	sudo mkfs.vfat ${DEV_LOOP}p1
	sudo mkfs.xfs ${DEV_LOOP}p2

	mkdir -p ${MNT_BOOT_EFI} ${MNT_BOOT}
	sudo mount ${DEV_LOOP}p1 ${MNT_BOOT_EFI}
	sudo mount ${DEV_LOOP}p2 ${MNT_BOOT}

	rm -f ${fdisk_script}
}

# Pass -cdrom ${IMG_NAME} to qemu
single_partition() {
	sudo mkfs.vfat ${IMG_NAME}
	mkdir -p ${MNT_BOOT_EFI}
	sudo mount ${IMG_NAME} ${MNT_BOOT_EFI}
}

#single_partition
mk_multi_partitions_with_fdisk

sudo mkdir -p ${MNT_BOOT_EFI}/EFI/BOOT/
sudo mkdir -p ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/
sudo mkdir -p ${MNT_BOOT}/grub2/

gen_efi_grub_cfg() {
	# Get boot partition UUID
	local boot_uuid=$( lsblk -o uuid ${DEV_LOOP}p2 | sed 1d )
	echo "search --no-floppy --fs-uuid --set=boot ${boot_uuid}
set prefix=(\$boot)/grub2

export \$prefix
configfile \$prefix/grub.cfg
" | sudo tee ${1}
	sudo cat ${1}
}

# The following methods work fine, choise one.
# UEFI load grub2 directly
bootflow_1() {
	sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/BOOT/${IMG_BOOTEFI}
	gen_efi_grub_cfg ${MNT_BOOT_EFI}/EFI/BOOT/grub.cfg
	sudo tree ${MNT_BOOT_EFI}/EFI
}

# shim BOOT.EFI load grub2 directly
bootflow_2() {
	sudo cp /boot/efi/EFI/BOOT/${IMG_BOOTEFI} ${MNT_BOOT_EFI}/EFI/BOOT/${IMG_BOOTEFI}
	sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/BOOT/grub${EFI_ARCH}.efi
	gen_efi_grub_cfg ${MNT_BOOT_EFI}/EFI/BOOT/grub.cfg
	sudo tree ${MNT_BOOT_EFI}/EFI
}

# shim fallback bootflow
bootflow_3() {
	sudo cp /boot/efi/EFI/BOOT/${IMG_BOOTEFI} ${MNT_BOOT_EFI}/EFI/BOOT/${IMG_BOOTEFI}
	sudo cp /boot/efi/EFI/BOOT/fb${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/BOOT/fb${EFI_ARCH}.efi
	#sudo cp /boot/efi/EFI/${ID}/${IMG_BOOTCSV} ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/${IMG_BOOTCSV}
	# see https://github.com/rhboot/shim Makefile
	echo "shim${EFI_ARCH}.efi,${VENDOR_ID},,This is the boot entry for ${VENDOR_ID}" | \
		sudo iconv -t UCS-2LE -o ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/${IMG_BOOTCSV}
	sudo cp /boot/efi/EFI/${ID}/shim${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/shim${EFI_ARCH}.efi
	sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/grub${EFI_ARCH}.efi
	gen_efi_grub_cfg ${MNT_BOOT_EFI}/EFI/${VENDOR_ID}/grub.cfg
	sudo tree ${MNT_BOOT_EFI}/EFI
}

case ${BOOTFLOW} in
1) bootflow_1 ;;
2) bootflow_2 ;;
3) bootflow_3 ;;
*) echo >&2 "ERROR: unsupport bootflow ${BOOTFLOW}"; exit 1; ;;
esac

sudo cp grub.cfg ${MNT_BOOT}/grub2/grub.cfg
sudo sed -i "s|@BOOTFLOW@|${BOOTFLOW}|g" ${MNT_BOOT}/grub2/grub.cfg
sudo sed -i "s|@VENDOR@|${VENDOR_ID}|g" ${MNT_BOOT}/grub2/grub.cfg

sudo cp /boot/vmlinuz-$(uname -r) ${MNT_BOOT}/vmlinuz
sudo cp /boot/initramfs-$(uname -r).img ${MNT_BOOT}/initrd.img
sudo tree ${MNT_BOOT}

[[ ${DEV_LOOP} ]] && sudo fdisk -l ${DEV_LOOP}
sudo fdisk -l ${IMG_NAME}

# Do some clean
sudo umount ${MNT_BOOT_EFI}
sudo umount ${MNT_BOOT}
[[ ${DEV_LOOP} ]] && sudo losetup --detach ${DEV_LOOP}
rmdir ${MNT_BOOT_EFI} ${MNT_BOOT}


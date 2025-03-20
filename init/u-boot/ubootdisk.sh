#!/bin/bash
set -e

. config

kernel_root_dir=${LINUX_KERNEL_DIR}
dev_loop=

disk_file=uboot.disk

create_disk() {
	dd if=/dev/zero of=${disk_file} bs=1M count=1024
}

partition() {
	# Create GPT partition
	sgdisk -n 0:0:+900M -c 0:kernel ${disk_file}
	sgdisk -n 0:0:0 -c 0:rootfs ${disk_file}
	# Check partitions
	sgdisk -p ${disk_file}
}

makefs() {
	# Example: /dev/loop0
	dev_loop=$(sudo losetup -f)

	sudo losetup ${dev_loop} ${disk_file}
	sudo partprobe ${dev_loop}

	sudo mkfs.fat ${dev_loop}p1
	sudo mkfs.ext4 ${dev_loop}p2

	mkdir p1 p2
	sudo mount ${dev_loop}p1 p1
	sudo mount ${dev_loop}p2 p2

	# Copy files
	#  p1: kernel + dtb
	#   linux: aarch64 + vexpress_defconfig
	if [[ ! -z "${UBOOTDISK_PARTITION1_FILES[@]}" ]]; then
		sudo cp -a ${UBOOTDISK_PARTITION1_FILES[@]} p1/ || true
	else
		echo "WARNING: not found any files"
		read -p "Press any key to continue."
	fi
	sudo touch p1/hello.txt

	#  p2: rootfs
	sudo touch p2/hello.txt
}

destroy() {
	sudo umount p1 p2 || true
	rmdir p1 p2 || true
	sudo losetup -d ${dev_loop} || true
}

usage() {
	echo "
create u-boot disk:

-n, --disk-name   [NAME]         specify disk name, default: ${disk_file}

-v, --verbose
-h, --help
"
}

# __main__
while true
do
case $1 in
-n | --disk-name)
	shift
	disk_file=$1
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

create_disk
partition
makefs
destroy
# a.raw to a.qcow2
qemu-img convert -O qcow2 ${disk_file} ${disk_file%.*}.qcow2
echo "Success.."

#!/bin/bash

. config

# qemu: docs/system/arm/orangepi.rst
kernel_run_arm_1() {
	qemu-system-arm  -M orangepi-pc -nic user -nographic \
		-kernel ${LINUX_KERNEL_DIR}/arch/arm/boot/zImage \
		-append 'console=ttyS0,115200' \
		-dtb ${LINUX_KERNEL_DIR}/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb
}

kernel_run_arm_2() {
	qemu-system-arm  -M orangepi-pc -nic user -nographic \
		-kernel ${LINUX_KERNEL_DIR}/arch/arm/boot/zImage \
		-append 'console=ttyS0,115200 root=/dev/mmcblk0p2' \
		-dtb ${LINUX_KERNEL_DIR}/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb \
		-sd uboot.disk
}

usage()
{
	cat <<-EOF

	compile [type]

	type: test-arm test-arm-disk

		-v, --verbose
		-h, --help

	EOF
}

while true
do
case $1 in
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
*)
	break
	;;
esac
done

case $1 in
test-arm)
	kernel_run_arm_1
	;;
test-arm-disk)
	kernel_run_arm_2
	;;
*)
	usage
	echo "ERROR: Unsupport '$1'"
	exit 1
	;;
esac

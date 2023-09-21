#!/bin/bash

. config

kernel_compile_cross_aarch64() {
	sudo make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- vexpress_defconfig
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j8
}

# qemu: docs/system/arm/orangepi.rst
kernel_compile_cross_arm() {
	sudo ARCH=arm CROSS_COMPILE=arm-linux-gnu- make mrproper
	sudo ARCH=arm CROSS_COMPILE=arm-linux-gnu- make sunxi_defconfig
	sudo ARCH=arm CROSS_COMPILE=arm-linux-gnu- make menuconfig
	sudo ARCH=arm CROSS_COMPILE=arm-linux-gnu- make -j8
}

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

	type: cross-aarch64 cross-arm test-cross-arm test-cross-arm-disk

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
cross-aarch64)
	pushd ${LINUX_KERNEL_DIR}
	kernel_compile_cross_aarch64
	popd
	;;
cross-arm)
	pushd ${LINUX_KERNEL_DIR}
	kernel_compile_cross_arm
	popd
	;;
test-cross-arm)
	kernel_run_arm_1
	;;
test-cross-arm-disk)
	kernel_run_arm_2
	;;
*)
	usage
	echo "ERROR: Unsupport '$1'"
	exit 1
	;;
esac

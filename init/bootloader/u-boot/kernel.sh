#!/bin/bash

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
		-kernel /home/rongtao/Git/linux/arch/arm/boot/zImage \
		-append 'console=ttyS0,115200' \
		-dtb /home/rongtao/Git/linux/arch/arm/boot/dts/allwinner/sun8i-h3-orangepi-pc.dtb
}


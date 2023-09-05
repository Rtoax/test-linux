#!/bin/bash

kernel_compile_cross_aarch64() {
	sudo make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- vexpress_defconfig
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j8
}

#!/bin/bash
# u-boot: https://source.denx.de/u-boot/u-boot.git

compile_qemu_x86_64()
{
	sudo make clean
	sudo make qemu-x86_64_defconfig
	sudo make -j8
}

compile_qemu_aarch64()
{
	sudo make clean
	sudo make qemu-arm64_defconfig
	sudo make -j8
}

compile_cross_aarch64()
{
	sudo make clean
	sudo make CROSS_COMPILE=aarch64-linux-gnu- qemu_arm64_defconfig
	sudo make CROSS_COMPILE=aarch64-linux-gnu- -j8
}

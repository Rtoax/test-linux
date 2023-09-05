#!/bin/bash
# u-boot: https://source.denx.de/u-boot/u-boot.git

. config

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
	sudo make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- qemu_arm64_defconfig
	sudo make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- -j8
}

compile_cross_arm()
{
	sudo make clean
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnu- qemu_arm_defconfig
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnu- -j8
}

usage()
{
	cat <<-EOF

	compile [type]

	type: x86_64 aarch64 cross-aarch64 cross-arm

		-v, --verbose
		-h, --help

	EOF
}

compile_type=$(uname -m)

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
x86_64)
	pushd ${U_BOOT_DIR}
	compile_qemu_x86_64
	popd
	;;
aarch64)
	pushd ${U_BOOT_DIR}
	compile_qemu_aarch64
	popd
	;;
cross-aarch64)
	pushd ${U_BOOT_DIR}
	compile_cross_aarch64
	popd
	;;
cross-arm)
	pushd ${U_BOOT_DIR}
	compile_cross_arm
	popd
	;;
*)
	usage
	echo "ERROR: Unsupport '$1'"
	exit 1
	;;
esac

#!/bin/bash
# u-boot: https://source.denx.de/u-boot/u-boot.git

. config

compile_qemu_x86_64()
{
	sudo make clean
	sudo make qemu-x86_64_defconfig
	sudo make -j8
}

compile_qemu_x86_64_custom()
{
	cp ${WORK_DIR}/configs/qemu-x86_64_defconfig ${U_BOOT_DIR}/configs
	sudo make clean
	sudo make qemu-x86_64_defconfig
	sudo make -j8
}

__compile_aarch64()
{
	local config=$1
	sudo make clean
	sudo make ${config}
	sudo make -j8
}

compile_aarch64_qemu()
{
	__compile_aarch64 qemu_arm64_defconfig
}

__compile_cross_aarch64() {
	local config=$1
	local cross_args

	[[ $(uname -m) != aarch64 ]] && cross_args="ARCH=arm CROSS_COMPILE=aarch64-linux-gnu-"
	sudo make clean
	sudo make ${cross_args} ${config}
	sudo make ${cross_args} -j8
}
compile_cross_aarch64_qemu()
{
	__compile_cross_aarch64 qemu_arm64_defconfig
}

compile_cross_aarch64_vexpress_aemv8a_semi()
{
	__compile_cross_aarch64 vexpress_aemv8a_semi_defconfig
}

compile_cross_aarch64_custom()
{
	cp ${WORK_DIR}/configs/qemu_arm64_defconfig ${U_BOOT_DIR}/configs
	cp ${WORK_DIR}/arch/arm/dts/qemu-arm64.dts ${U_BOOT_DIR}/arch/arm/dts/qemu-arm64-custom.dts

	__compile_cross_aarch64 qemu_arm64_defconfig
}

compile_cross_aarch64_nanopc_t4_rk3399()
{
	__compile_cross_aarch64 nanopc-t4-rk3399_defconfig
}

compile_cross_aarch64_rpi()
{
	__compile_cross_aarch64 rpi_arm64_defconfig
}

__compile_cross_arm()
{
	local config=${1}
	sudo make clean
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnu- ${config}
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnu- -j8
}

compile_cross_arm_qemu()
{
	__compile_cross_arm qemu_arm_defconfig
}

compile_cross_arm_orangepi()
{
	__compile_cross_arm orangepi_one_defconfig
}

# ref: <ubuntu16.04 qemu arm u-boot> https://juejin.cn/post/6844903606500458510
compile_cross_arm_vexpress_ca9x4()
{
	__compile_cross_arm vexpress_ca9x4_defconfig
}

usage()
{
	echo "
compile [opt] [type]

type:
	x86_64
	x86_64-custom

	aarch64-qemu

	cross-aarch64 [config]
	cross-aarch64-qemu
	cross-aarch64-vexpress_aemv8a_semi
	cross-aarch64-nanopc-t4              # Failed
	cross-aarch64-rpi
	cross-aarch64-custom                 # OK

	cross-arm-qemu
	cross-arm-vexpress_ca9x4             # OK
	cross-arm-orangepi

opt:
	-u, --uboot-dir [directory]
	-v, --verbose
	-h, --help
	"
}

compile_type=$(uname -m)

while true
do
case $1 in
-u | --uboot-dir)
	shift
	U_BOOT_DIR=$1
	if [[ ! -d ${U_BOOT_DIR} ]]; then
		echo "ERROR: ${U_BOOT_DIR} is not directory"
		exit 1
	fi
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
	echo "ERROR: Unknown $1"
	exit 1
	;;
*)
	break
	;;
esac
done

case $1 in
x86_64)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_qemu_x86_64
	popd
	;;
x86_64-custom)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_qemu_x86_64_custom
	popd
	;;
aarch64-qemu)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_aarch64_qemu
	popd
	;;
cross-aarch64)
	shift
	config=$1
	if [[ -z ${config} ]]; then
		echo "ERROR: ./compile-uboot.sh cross-aarch64 [CONFIG]"
		exit 1
	fi
	if [[ ! -e ${U_BOOT_DIR}/configs/${config} ]]; then
		echo "ERROR: ${U_BOOT_DIR}/configs/${config} is not exist."
		echo "       see: ls ${U_BOOT_DIR}/configs/"
		exit 1
	fi
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	__compile_cross_aarch64 ${config}
	popd
	;;
cross-aarch64-qemu)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_aarch64_qemu
	popd
	;;
cross-aarch64-vexpress_aemv8a_semi)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_aarch64_vexpress_aemv8a_semi
	popd
	;;
cross-aarch64-custom)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_aarch64_custom
	popd
	;;
cross-aarch64-nanopc-t4)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_aarch64_nanopc_t4_rk3399
	popd
	;;
cross-aarch64-rpi)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_aarch64_rpi
	popd
	;;
cross-arm-qemu)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_arm_qemu
	popd
	;;
cross-arm-vexpress_ca9x4)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_arm_vexpress_ca9x4
	popd
	;;
cross-arm-orangepi)
	pushd ${U_BOOT_DIR}
	sudo git clean -dfx
	compile_cross_arm_orangepi
	popd
	;;
*)
	usage
	echo "ERROR: Unsupport '$1'"
	exit 1
	;;
esac

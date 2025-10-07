#!/bin/bash
# Install and uninstall kernel from upstream linux
#
# Refs:
# - https://github.com/torvalds/linux
# - https://git.kernel.org/pub/scm/linux/kernel/git/bpf/bpf-next
# - https://git.kernel.org/pub/scm/linux/kernel/git/bpf/bpf
#
# Copyright (c) 2024-2025 Rong Tao
#
set -e

. /etc/os-release

readonly prog=kinstall
ARGS=$@

verbose=
kver=

error() {
	echo -en >&2 "\033[31m"
	echo -e >&2 "ERROR: ${@}"
	echo -en >&2 "\033[m"
	exit 1
}

warning() {
	echo -en >&2 "\033[34m"
	echo -e >&2 "WARNING: ${@}"
	echo -en >&2 "\033[m"
}

check_root() {
	if [[ $(id -u) -ne 0 ]]; then
		error "Must run with root(sudo)"
	fi
}

check_kver() {
	if [[ -z ${kver} ]]; then
		error "Must specify kernel version"
	fi
}

cross_compile_env()
{
	export ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
	export CC=aarch64-linux-gnu-gcc
	export INSTALL_PATH=$PWD
	export INSTALL_MOD_PATH=$PWD/modules
	export INSTALL_HDR_PATH=$PWD/headers
}

kernel_compile_cross_aarch64() {
	make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- vexpress_defconfig
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
}

# qemu: docs/system/arm/orangepi.rst
kernel_compile_cross_arm() {
	ARCH=arm CROSS_COMPILE=arm-linux-gnu- make mrproper
	ARCH=arm CROSS_COMPILE=arm-linux-gnu- make sunxi_defconfig
	ARCH=arm CROSS_COMPILE=arm-linux-gnu- make menuconfig
	ARCH=arm CROSS_COMPILE=arm-linux-gnu- make -j$(nproc)
}

config_kernel()
{
	# to see a list of new configuration symbols
	cp /boot/config-$(uname -r) .config
	make listnewconfig

	# Start to config

	make oldconfig

	# Or trim down the kernel and tailor it to your system
	lsmod > /tmp/my-lsmod
	make LSMOD=/tmp/my-lsmod localmodconfig

	# Or use TUI
	make menuconfig
}

compile()
{
	make -j$(nproc)
}

install_from_source()
{
	check_root
	check_kver

	# install
	make modules_install
	make headers_install
	make install

	# Update grub
	# If RHEL like OS:
	if [[ " fedora " =~ " ${ID} " ]]; then
		grub2-mkconfig -o /boot/grub2/grub.cfg
		grubby --set-default /boot/vmlinuz-${kver}

		grubby --info=ALL | more
		grubby --default-index
		grubby --default-kernel
	# If Debian like OS:
	elif [[ " debian " =~ " ${ID} " ]]; then
		update-grub
	fi

	cp .config /boot/config-${kver}
}

uninstall_kernel()
{
	local version=$1
	local modules=/lib/modules/$version
	local vmlinuz=/boot/vmlinuz-$version
	local initramfs=/boot/initramfs-$version.img
	local config=/boot/config-$version

	local curr_version=$(uname -r)

	check_root
	check_kver

	[[ $version == $curr_version ]] && error "Can't remove running kernel"

	test ! -d $modules && warning "$modules not exist"
	test ! -f $vmlinuz && warning "$vmlinuz not exist"
	test ! -f $initramfs && warning "$initramfs not exist"

	grubby --remove-kernel /boot/vmlinuz-${version}

	rm -rf $modules
	rm -f $vmlinuz $initramfs $config

	grub2-mkconfig -o /boot/grub2/grub.cfg
}

__usage__() {
	echo -e "
NAME
	${prog} - Install and uninstall kernel from upstream linux

SYNOPSIS
	${prog} [OPTION]... [SUBCOMMANDS] [OPTION]...

OPTIONS
	-k, --kver [VERSION]            set kernel version
	-h, --help                      display this info
	-v, --verbose                   run with verbose mode

SUBCOMMANDS
	install-from-source
	uninstall

SEE ALSO
	gcc(1), etc.
"
	exit ${1-0}
}

__getopt__() {
	TEMP_ARGS=$(getopt --options k:vh \
		--long kver: \
		--long verbose \
		--long help \
		--name ${prog} -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP_ARGS"

	while true; do
		case $1 in
		-k | --kver)
			shift
			kver=$1
			shift
			;;
		-h | --help)
			shift
			__usage__
			;;
		-v | --verbose)
			shift
			verbose=YES
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ ${verbose} ]]; then
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
	fi
	ARGS="$@"
}

__getopt__ $@
eval set -- "$ARGS"

while true; do
	case $1 in
	install-from-source)
		shift
		__getopt__ $@
		eval set -- "$ARGS"
		install_from_source
		;;
	uninstall)
		shift
		__getopt__ $@
		eval set -- "$ARGS"
		uninstall_kernel
		;;
	*)
		if [[ $1 ]]; then
			__getopt__ $@
			eval set -- "$ARGS"
		else
			__usage__
			error "no subcommand specified!!!"
			break;
		fi
		;;
	esac
done

#!/bin/bash

set -e

cross_compile_env()
{
	export ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
	export CC=aarch64-linux-gnu-gcc
	export INSTALL_PATH=$PWD
	export INSTALL_MOD_PATH=$PWD/modules
	export INSTALL_HDR_PATH=$PWD/headers
}

config_kernel()
{
	make oldconfig

	# Or trim down the kernel and tailor it to your system
	lsmod > /tmp/my-lsmod
	make LSMOD=/tmp/my-lsmod localmodconfig

	# Or use TUI
	make menuconfig
}

install_from_source()
{
	# Compile and install
	sudo make -j$(nproc)
	sudo make modules_install
	sudo make headers_install
	sudo make install

	# Update grub
	sudo grub2-mkconfig -o /boot/grub2/grub.cfg
	sudo grubby --set-default /boot/vmlinuz-6.0.0-rc4+

	# Confirm
	sudo grubby --info=ALL | more
	sudo grubby --default-index
	sudo grubby --default-kernel
}

uninstall_kernel()
{
	local version=$1
	local modules=/lib/modules/$version
	local vmlinuz=/boot/vmlinuz-$version
	local initramfs=/boot/initramfs-$version.img
	local config=/boot/config-$version.img

	local curr_version=$(uname -r)

	test $version == $curr_version && \
		echo "Can't remove running kernel" && exit 1

	test ! -d $modules && \
		echo "$modules not exist" && exit 1
	test ! -f $vmlinuz && \
		echo "$vmlinuz not exist" && exit 1
	test ! -f $initramfs && \
		echo "$initramfs not exist" && exit 1


	sudo grubby --remove-kernel /boot/vmlinuz-${version}

	sudo rm -rf $modules
	sudo rm -f $vmlinuz $initramfs $config

	sudo grub2-mkconfig -o /boot/grub2/grub.cfg

	# TODO
	# grubby --set-default /boot/vmlinuz-...
}

case $1 in
	install_from_source)
		install_from_source
		;;
	*)
echo -e "
  install_from_source
"
		;;
esac


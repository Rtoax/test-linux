#!/bin/bash
set -e
. /etc/os-release

cross_compile_env()
{
	export ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
	export CC=aarch64-linux-gnu-gcc
	export INSTALL_PATH=$PWD
	export INSTALL_MOD_PATH=$PWD/modules
	export INSTALL_HDR_PATH=$PWD/headers
}

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
	sudo make -j$(nproc)
}

install_from_source()
{
	# https://github.com/torvalds/linux
	# https://git.kernel.org/pub/scm/linux/kernel/git/bpf/bpf-next
	local kver="6.17-rc3"

	# install
	sudo make modules_install
	sudo make headers_install
	sudo make install

	# Update grub
	# If RHEL like OS:
	if [[ " fedora " =~ " ${ID} " ]]; then
		sudo grub2-mkconfig -o /boot/grub2/grub.cfg
		sudo grubby --set-default /boot/vmlinuz-${kver}
		sudo cp .config /boot/config-${kver}

		sudo grubby --info=ALL | more
		sudo grubby --default-index
		sudo grubby --default-kernel
	# If Debian like OS:
	elif [[ " debian " =~ " ${ID} " ]]; then
		sudo update-grub
	fi
}

uninstall_kernel()
{
	local version=$1
	local modules=/lib/modules/$version
	local vmlinuz=/boot/vmlinuz-$version
	local initramfs=/boot/initramfs-$version.img
	local config=/boot/config-$version

	local curr_version=$(uname -r)

	test $version == $curr_version && \
		echo "ERROR: Can't remove running kernel" && exit 1

	test ! -d $modules && echo "WARNING: $modules not exist"
	test ! -f $vmlinuz && echo "WARNING: $vmlinuz not exist"
	test ! -f $initramfs && echo "WARNING: $initramfs not exist"

	sudo grubby --remove-kernel /boot/vmlinuz-${version}

	sudo rm -rf $modules
	sudo rm -f $vmlinuz $initramfs $config

	sudo grub2-mkconfig -o /boot/grub2/grub.cfg
}

case $1 in
install_from_source)
	shift
	install_from_source
	;;
uninstall)
	shift
	uninstall_kernel $@
	;;
*)
echo -e "
  install_from_source
  uninstall [kver]
"
		;;
esac

#!/bin/bash
# link: https://docs.fedoraproject.org/en-US/fedora-coreos/provisioning-raspberry-pi4/#_installing_fcos_and_booting_via_u_boot

RELEASE=37 # The target Fedora Release. Use the same one that current FCOS is based on.
TMP_DIR=$PWD/RPi4boot
mkdir -p $TMP_DIR/boot/efi/
sudo dnf install -y \
	--downloadonly \
	--release=$RELEASE \
	--forcearch=aarch64 \
	--destdir=${TMP_DIR} \
	uboot-images-armv8 bcm283x-firmware bcm283x-overlays

for rpm in ${TMP_DIR}/*rpm
do
	rpm2cpio $rpm | sudo cpio -idv -D ${TMP_DIR}
done

sudo cp ${TMP_DIR}/usr/share/uboot/rpi_4/u-boot.bin ${TMP_DIR}/boot/efi/rpi4-u-boot.bin

coreos_install() {
	FCOSDISK=/dev/sdX
	STREAM=stable # or `next` or `testing`
	sudo coreos-installer install -a aarch64 -s $STREAM -i config.ign $FCOSDISK
}

#!/bin/bash

xorrisofs_x86_64() {
	local DIR=/home/isos/CentOS-x86_64-dvd-202212300927

	# This command comes from lorax log, see pylorax.log
	sudo xorrisofs \
		-o boot.iso \
		-isohybrid-mbr /usr/share/syslinux/isohdpfx.bin \
		-b isolinux/isolinux.bin \
		-c isolinux/boot.cat \
		-boot-load-size 4 \
		-boot-info-table \
		-no-emul-boot \
		-eltorito-alt-boot \
		-e images/efiboot.img \
		-no-emul-boot \
		-isohybrid-gpt-basdat \
		-R -J \
		-V CENTOS \
		-graft-points \
			.discinfo=${DIR}/.discinfo \
			images/install.img=${DIR}/images/install.img \
			isolinux=${DIR}/isolinux \
			images/pxeboot=${DIR}/images/pxeboot \
			EFI/BOOT=${DIR}/EFI/BOOT \
			images/efiboot.img=${DIR}/images/efiboot.img \
			LICENSE=${DIR}/LICENSE
}

xorrisofs_aarch64() {
	local DIR=/mnt/iso/

	# This command comes from lorax log, see pylorax.log
	sudo xorrisofs \
		-o boot.iso \
		-eltorito-alt-boot \
		-e images/efiboot.img \
		-no-emul-boot \
		-R -J \
		-V CENTOS \
		-graft-points \
			.discinfo=${DIR}/.discinfo \
			images/pxeboot=${DIR}/images/pxeboot \
			images/install.img=${DIR}/images/install.img \
			EFI/BOOT=${DIR}/EFI/BOOT \
			images/efiboot.img=${DIR}/images/efiboot.img \
			LICENSE=${DIR}/LICENSE
}

if [[ $(uname -m) == x86_64 ]]; then
	xorrisofs_x86_64
elif [[ $(uname -m) == aarch64 ]]; then
	xorrisofs_aarch64
fi

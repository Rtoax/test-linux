#!/bin/bash
# Working under linux source code.
set -ex

MACHINE_ID=$(cat /etc/machine-id)
KVER=$(make kernelrelease)
UKI=/boot/efi/EFI/Linux/${MACHINE_ID}-${KVER}.efi

use_ukify() {
	sudo ukify build \
		--linux=/boot/vmlinuz-${KVER} \
		--initrd=/boot/initramfs-${KVER}.img \
		--cmdline=@/etc/kernel/cmdline \
		--output=${UKI}
}

use_dracut() {
	sudo dracut --uefi --force \
		--kernel-image /boot/vmlinuz-${KVER} \
		--kver ${KVER} \
		${UKI}
}

# make menuconfig
# make -j$(nproc)
# sudo make modules_install
# sudo make headers_install
# sudo make install

# Or use use_ukify()
use_dracut

sudo du -sh ${UKI}

# sudo grub2-mkconfig -o /boot/grub2/grub.cfg
# sudo grubby --set-default /boot/vmlinuz-${KVER}

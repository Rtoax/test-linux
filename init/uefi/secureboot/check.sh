#!/bin/bash

# Check secure boot state, need mokutil
check_secureboot() {
	mokutil --sb-state

	# disable secure boot temporarily on startup with MOK manager:
	# $ sudo mokutil --disable-validation
	#
	# To re-enable it (please note that you won't be able to boot the
	# kernels you build if you re-enable):
	# $ sudo mokutil --enable-validation
}

if [[ -e /sys/firmware/efi ]]; then
	echo "UEFI boot"
	echo $(cat /sys/firmware/efi/fw_platform_size)bit UEFI System
	check_secureboot
else
	echo "Not UEFI boot"
fi

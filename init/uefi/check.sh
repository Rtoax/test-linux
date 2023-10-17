#!/bin/bash

# Check secure boot state, need mokutil
check_secureboot() {
	mokutil --sb-state
}

if [[ -e /sys/firmware/efi ]]; then
	echo "UEFI boot"
	echo $(cat /sys/firmware/efi/fw_platform_size)bit UEFI System
	check_secureboot
else
	echo "Not UEFI boot"
fi

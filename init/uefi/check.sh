#!/bin/bash

if [[ -e /sys/firmware/efi ]]; then
	echo "UEFI boot"
	# Check secure boot state, need mokutil
	mokutil --sb-state
	echo $(cat /sys/firmware/efi/fw_platform_size)bit UEFI System
else
	echo "Not UEFI boot"
fi

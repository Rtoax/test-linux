#!/bin/bash

if [[ -e /sys/firmware/efi ]]; then
	echo "UEFI boot"
	# Check secure boot state, need mokutil
	mokutil --sb-state
else
	echo "Not UEFI boot"
fi

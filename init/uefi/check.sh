#!/bin/bash

if [[ -e /sys/firmware/efi ]]; then
	echo "UEFI boot"
else
	echo "Not UEFI boot"
fi

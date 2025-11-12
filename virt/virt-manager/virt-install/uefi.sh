#!/bin/bash

# https://fedoraproject.org/wiki/Using_UEFI_with_QEMU
sudo virt-install --name f20-uefi \
	--ram 2048 --disk size=20 \
	--boot uefi \
	--location https://dl.fedoraproject.org/pub/fedora/linux/releases/22/Workstation/x86_64/os/

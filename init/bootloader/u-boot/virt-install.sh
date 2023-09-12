#!/bin/bash

. config

# TODO
virt-install \
	--arch=aarch64 \
	--osinfo=rhel9-unknown \
	--name=$(mktemp --dry-run test-vm-XXXXXX) \
	--cdrom ${CCLINUX_ISO_AARCH64} \
	--boot uefi,firmware.feature0.name=secure-boot,firmware.feature0.enabled=no \
	--boot loader=${U_BOOT_DIR}/u-boot.rom

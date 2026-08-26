# SPDX-License-Identifier: GPL-3.0
include file.mk

subdir-y += acpi
subdir-y += bios
subdir-y += firmware
subdir-y += grub
subdir-y += kernel
subdir-y += initrd
subdir-y += modules
subdir-y += power
subdir-y += systemd
subdir-$(fexist,/sys/firmware/efi) += uefi

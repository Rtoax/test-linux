# SPDX-License-Identifier: GPL-3.0
target-y += kexec
target-y += poweroff
target-y += reboot

target-libso-y := libreboot_helpers.so
target-liba-y := libreboot_helpers.a

libreboot_helpers.a-objs := ${OUTPUT}reboot_helpers.a.o
libreboot_helpers.so-objs := ${OUTPUT}reboot_helpers.so.o

CFLAGS_kexec := -DKEXEC=1
CFLAGS_poweroff := -DPOWEROFF=1

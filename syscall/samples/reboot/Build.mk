# SPDX-License-Identifier: GPL-3.0
target-y += kexec
target-y += poweroff
target-y += reboot

CFLAGS_kexec := -DKEXEC=1
CFLAGS_poweroff := -DPOWEROFF=1

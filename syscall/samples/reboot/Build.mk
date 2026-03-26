# SPDX-License-Identifier: GPL-3.0
target-y += reboot
target-y += poweroff

CFLAGS_poweroff := -DPOWEROFF=1

# SPDX-License-Identifier: GPL-3.0
include efibootmgr.mk

subdir-y += secureboot
subdir-y += efivars
subdir-${HAVE_EFIBOOTMGR} += efibootmgr

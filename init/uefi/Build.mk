# SPDX-License-Identifier: GPL-3.0
include efibootmgr.mk

subdir-y += secureboot
subdir-y += efivarfs
subdir-${HAVE_EFIBOOTMGR} += efibootmgr

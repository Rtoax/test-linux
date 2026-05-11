# SPDX-License-Identifier: GPL-3.0
include efibootmgr.mk

subdir-y += secureboot
subdir-y += efivarfs

target-prog-${HAVE_EFIBOOTMGR} += efibootmgr.sh

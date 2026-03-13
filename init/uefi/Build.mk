# SPDX-License-Identifier: GPL-3.0
subdir-y += secureboot
subdir-y += efivarfs

target-prog-y += efibootmgr.sh
target-prog-y += version.sh version.sh.1 version.sh.2 version.sh.3

PROG_ARGS_version.sh.1 := --specmajor
PROG_ARGS_version.sh.2 := --specminor
PROG_ARGS_version.sh.3 := --vendor

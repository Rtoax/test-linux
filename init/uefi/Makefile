# SPDX-License-Identifier: GPL-3.0
subdir-y := secureboot

target-shell-y := efibootmgr.sh
target-shell-y += efivarfs.sh
target-shell-y += version.sh version.sh.1 version.sh.2 version.sh.3

SHELL_ARGS_version.sh.1 := --specmajor
SHELL_ARGS_version.sh.2 := --specminor
SHELL_ARGS_version.sh.3 := --vendor

include main.mk

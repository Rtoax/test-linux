# SPDX-License-Identifier: GPL-3.0
subdir-y := secureboot

target-shell-y := efibootmgr.sh
target-shell-y += efivarfs.sh
target-shell-y += version.sh version.sh.1 version.sh.s

SHELL_ARGS_version.sh.1 := --major
SHELL_ARGS_version.sh.2 := --minor

include main.mk

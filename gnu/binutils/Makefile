# SPDX-License-Identifier: GPL-3.0
include binutils.mk

target-shell-y := version.sh version.sh.1 version.sh.2

SHELL_ARGS_version.sh.1 := --major
SHELL_ARGS_version.sh.2 := --minor

subdir-y := bfd
subdir-y += objdump
subdir-y += opcode

include main.mk

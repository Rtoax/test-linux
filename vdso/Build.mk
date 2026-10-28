# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao. All rights reserved.
include vdso.mk

subdir-y += abi
subdir-y += scripts
subdir-y += test
subdir-y += modules
subdir-y += nvDSO
subdir-y += vvar

prep-y += ${VDSO_NAME}

prog-y += dump.sh
prog-y += dump.sh.1
prog-y += dump.sh.2
prog-y += layout.sh

PROG_ARGS_dump.sh.1 := -n 1.elf
PROG_ARGS_dump.sh.2 := -s -n 2.elf

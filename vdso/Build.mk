# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
include vdso.mk

subdir-y += abi
subdir-y += scripts
subdir-y += test
subdir-y += nvDSO
subdir-y += vvar

target-prep-y += ${VDSO_NAME}
target-prog-y += dump.sh
target-prog-y += layout.sh

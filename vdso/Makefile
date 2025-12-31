# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2025 Rong Tao
include vdso.mk

subdir-y := abi
subdir-y += scripts
subdir-y += test
subdir-y += nvDSO
subdir-y += vvar

target-prep-y := ${VDSO_NAME}
target-shell-y := layout.sh

include main.mk

${VDSO_NAME}:
	$(call log_exe,VDSO,,$(@))
	$(call gen_vdso_elf,${@})

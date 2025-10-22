# SPDX-License-Identifier: GPL-3.0
include vdso.mk

subdir-y := abi
subdir-y += scripts
subdir-y += test
subdir-y += nvDSO
subdir-y += vvar/scripts/

target-prep-y := ${VDSO_NAME}
target-shell-y := layout.sh

include ../template/main.mk

${VDSO_NAME}:
	$(call log_tgt_exe,VDSO,,$(@))
	$(call gen_vdso_elf,${@})

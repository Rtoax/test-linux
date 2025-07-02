# SPDX-License-Identifier: GPL-3.0
include vdso.mk

sub-dir := abi
sub-dir += scripts
sub-dir += test
sub-dir += nvDSO
sub-dir += vvar/scripts/

TARGETS_PREP := ${VDSO_NAME}
TARGETS_SHELL := layout.sh

include ../template/main.mk

${VDSO_NAME}:
	$(call log_tgt_exe,VDSO,,$(@))
	$(call gen_vdso_elf)

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
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(call gen_vdso_elf)

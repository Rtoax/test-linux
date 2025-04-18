# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include vdso.mk

sub-dir := abi
sub-dir += scripts
sub-dir += test
sub-dir += nvDSO
sub-dir += vvar/scripts/

include ../template/subdir-header.mk

$(info CMDLINE_VDSO=${CMDLINE_VDSO})

.PHONY: build
build: ${VDSO_NAME} $(sub-dir-build)
	@${SHELL} ./layout.sh

${VDSO_NAME}:
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(call gen_vdso_elf)

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -rf *.so.1 *.bt.out

include ../template/subdir-footer.mk

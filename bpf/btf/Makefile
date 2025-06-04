# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include btf.mk

sub-dir := examples

ifneq ($(call vmlinux_has_struct,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_struct,task_struct)>)
endif
ifneq ($(call vmlinux_has_sym,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_sym,task_struct)>)
endif

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) vmlinux.h
	@echo -e "  \033[1;33mDone\033[m"

include ../bpftool/vmlinux.h.mk

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  RM  \033[1mvmlinux.h\033[m"
	${Q}rm -f vmlinux.h

include ../../template/subdir-footer.mk

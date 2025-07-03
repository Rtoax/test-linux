# SPDX-License-Identifier: GPL-3.0
Q ?= @
BPFTOOL ?= bpftool
VMLINUX_H ?= vmlinux.h

define gen_vmlinux_h
	$(Q)${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > ${1}
endef

${VMLINUX_H}:
	@echo -e "  BPFTOOL  \033[1;32m$(@)\033[m"
	$(call gen_vmlinux_h,${VMLINUX_H})

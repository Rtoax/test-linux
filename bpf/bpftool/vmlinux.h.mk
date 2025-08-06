# SPDX-License-Identifier: GPL-3.0
Q ?= @
BPFTOOL ?= bpftool
VMLINUX_H ?= vmlinux.h

define gen_btf_h
	$(Q)${BPFTOOL} btf dump file /sys/kernel/btf/${1} format c > ${2}
endef

define gen_vmlinux_h
$(call gen_btf_h,vmlinux,${VMLINUX_H})
endef

${VMLINUX_H}:
	@echo -e "  BPFTOOL  \033[1;32m$(@)\033[m"
	$(call gen_vmlinux_h,${VMLINUX_H})

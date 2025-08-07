# SPDX-License-Identifier: GPL-3.0
Q := @
BPFTOOL := bpftool
VMLINUX_H := vmlinux.h

define bpf_gen_btf_h
	$(Q)${BPFTOOL} btf dump file /sys/kernel/btf/${1} format c > ${2}
endef

define bpf_gen_vmlinux_h
$(call bpf_gen_btf_h,vmlinux,${VMLINUX_H})
endef

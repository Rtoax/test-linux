# SPDX-License-Identifier: GPL-3.0
SHELL := bash
Q := @
BPFTOOL := bpftool
VMLINUX_H := vmlinux.h

define bpf_gen_btf_h
	$(Q)${BPFTOOL} btf dump file /sys/kernel/btf/${1} format c > ${2}
endef

define bpf_gen_vmlinux_h
$(call bpf_gen_btf_h,vmlinux,${VMLINUX_H})
endef

define chk_vmlinux_h
$(shell if [[ ! -e ${VMLINUX_H} ]]; then \
		mkdir -p $$(dirname ${VMLINUX_H}); \
		${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > ${VMLINUX_H}; \
	fi)
endef

# $1 - struct name, like task_struct
define vmlinux_has_struct
$(call chk_vmlinux_h)$(shell if [[ "$$(grep -wo '^struct ${1} {' ${VMLINUX_H})" ]]; then \
		echo 'y'; \
		else echo 'n'; \
	fi)
endef

# $1 - symbol name, like bpf_task_from_pid, task_struct.
define vmlinux_has_sym
$(call chk_vmlinux_h)$(shell if [[ "$$(grep -wo '${1}' ${VMLINUX_H})" ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

ifneq ($(call vmlinux_has_struct,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_struct,task_struct)>)
endif
ifneq ($(call vmlinux_has_sym,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_sym,task_struct)>)
endif


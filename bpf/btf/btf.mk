# SPDX-License-Identifier: GPL-3.0

VMLINUX_H ?= vmlinux.h
BPFTOOL ?= bpftool

# $1 - struct name, like task_struct
define vmlinux_has_struct
$(shell if [[ ! -e ${VMLINUX_H} ]]; then \
		mkdir -p $$(dirname ${VMLINUX_H}); \
		${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > ${VMLINUX_H}; \
	fi; \
	if [[ "$$(grep -wo '^struct ${1} {' ${VMLINUX_H})" ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

# $1 - symbol name, like bpf_task_from_pid, task_struct.
define vmlinux_has_sym
$(shell if [[ ! -e ${VMLINUX_H} ]]; then \
		mkdir -p $$(dirname ${VMLINUX_H}); \
		${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > ${VMLINUX_H}; \
	fi; \
	if [[ "$$(grep -wo '${1}' ${VMLINUX_H})" ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

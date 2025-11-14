# SPDX-License-Identifier: GPL-3.0
# Provide the following macro definitions:
#
# HAVE_BTF: Check your system support BTF or not
#
_BTF = 1

SHELL := bash
BPFTOOL := bpftool
VMLINUX_H := vmlinux.h
BTF_ROOT := /sys/kernel/btf
HAVE_BTF := yes

ifeq ($(wildcard ${BTF_ROOT}),)
  $(warning Not found BTF in your system, see CONFIG_DEBUG_INFO_BTF in your kernel config!!)
  HAVE_BTF :=
endif

ifneq (${HAVE_BTF},)
# Use the bpftool command to generate a series of btf header files.
# $1 - btf file name
# $2 - btf header file name
define bpf_gen_btf_h
${BPFTOOL} btf dump file ${BTF_ROOT}/${1} format c > ${2}
endef
else
define bpf_gen_btf_h
$(error You system not support BTF, see CONFIG_DEBUG_INFO_BTF)
endef
endif

define bpf_gen_vmlinux_h
$(call bpf_gen_btf_h,vmlinux,${VMLINUX_H})
endef

define chk_vmlinux_h
$(shell if [[ ! -e ${VMLINUX_H} ]]; then \
		mkdir -p $$(dirname ${VMLINUX_H}); \
		$(call bpf_gen_vmlinux_h); \
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
# return: n if failed, y if success
define vmlinux_has_sym
$(call chk_vmlinux_h)$(shell if [[ "$$(grep -wo '${1}' ${VMLINUX_H})" ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

export HAVE_BTF

ifdef DEBUG
  $(info HAVE_BTF = ${HAVE_BTF})
endif

ifneq (${HAVE_BTF},)
  ifneq ($(call vmlinux_has_struct,task_struct),y)
    $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_struct,task_struct)>)
  endif
  ifneq ($(call vmlinux_has_sym,task_struct),y)
    $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_sym,task_struct)>)
  endif
endif

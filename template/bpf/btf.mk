# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BTF: Check your system support BTF or not
#
_BPF_BTF_MK = 1

include shell.mk
include bpf/bpftool.mk

VMLINUX_H := vmlinux.h
BTF_ROOT := /sys/kernel/btf
HAVE_BTF := y

ifeq ($(wildcard ${BTF_ROOT}),)
  $(warning Not found BTF in your system, see CONFIG_DEBUG_INFO_BTF in your kernel config!!)
  HAVE_BTF :=
endif

ifneq (${HAVE_BTF},)
# Use the bpftool command to generate a series of btf header files.
# $1 - btf file name under /sys/kernel/btf
# $2 - btf header file name or fullpath
define btf_gen_hdr
  mkdir -p $$(dirname ${2}); \
  ${BPFTOOL} btf dump file ${BTF_ROOT}/${1} format c > ${2}
endef
else
define btf_gen_hdr
$(error Your system not support BTF, see CONFIG_DEBUG_INFO_BTF)
endef
endif

define auto_gen_vmlinux_h
  if [[ ! -e ${VMLINUX_H} ]]; then \
    $(call btf_gen_hdr,vmlinux,${VMLINUX_H}); \
  fi
endef

# $1 - struct name, like task_struct
# return: n if failed, y if success
define vmlinux_has_struct
  $(call auto_gen_vmlinux_h); \
  if [[ "$$(grep -wo '^struct ${1} {' ${VMLINUX_H})" ]]; then \
    echo 'y'; \
  else \
    echo 'n'; \
  fi
endef
define vmlinux_has_struct_shell
$(shell $(call vmlinux_has_struct,${1}))
endef

# $1 - symbol name, like bpf_task_from_pid, task_struct.
# return: n if failed, y if success
define vmlinux_has_sym
  $(call auto_gen_vmlinux_h); \
  if [[ "$$(grep -wo '${1}' ${VMLINUX_H} 2>/dev/null)" ]]; then \
    echo y; \
  else \
    echo n; \
  fi
endef
define vmlinux_has_sym_shell
$(shell $(call vmlinux_has_sym,${1}))
endef

export HAVE_BTF

ifdef DEBUG
  $(info HAVE_BTF = ${HAVE_BTF})
endif

ifneq (${HAVE_BTF},)
  ifneq ($(shell $(call vmlinux_has_struct,task_struct)),y)
    $(error Not found task_struct in vmlinux.h)
  endif
  ifneq ($(shell $(call vmlinux_has_sym,task_struct)),y)
    $(error Not found task_struct in vmlinux.h)
  endif
endif

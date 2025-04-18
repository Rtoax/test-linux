# SPDX-License-Identifier: GPL-3.0

# kernel command line 'vdso=0' could disable vDSO
CMDLINE_VDSO := $(shell grep -o vdso=0 /proc/cmdline)

# see vdso(7)
VDSO_NAME := linux-vdso.so.1
VDSO_NAME_AARCH64 = linux-vdso.so.1
VDSO_NAME_ARM = linux-vdso.so.1
VDSO_NAME_X86_64 = linux-vdso.so.1
VDSO_NAME_X86_32 = linux-vdso.so.1

ifeq ($(shell uname -m),x86_64)
  VDSO_NAME := ${VDSO_NAME_X86_64}
endif
ifeq ($(shell uname -m),aarch64)
  VDSO_NAME := ${VDSO_NAME_AARCH64}
endif

KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso64.so
ifeq ($(wildcard $(KVDSO64)),)
  $(warning "WARNING: Not found ${KVDSO64}, use dump")
  KVDSO64 := ${VDSO_NAME}
endif

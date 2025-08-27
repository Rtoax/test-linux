# SPDX-License-Identifier: GPL-3.0
_VDSO = 1

VDSO_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

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

define gen_vdso_elf
@$(VDSO_ROOT)/dump.sh -s
endef

KVDSO64 :=
ifeq ($(shell uname -m),x86_64)
  KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso64.so
else ifeq ($(shell uname -m),aarch64)
  KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso.so
endif

ifeq ($(wildcard $(KVDSO64)),)
  $(warning "WARNING: Not found ${KVDSO64}, use dump")
  KVDSO64 := ${VDSO_NAME}
endif

ifdef DEBUG
  $(info CMDLINE_VDSO=${CMDLINE_VDSO})
  $(info VDSO_ROOT ${VDSO_ROOT})
  $(info VDSO_NAME ${VDSO_NAME})
endif

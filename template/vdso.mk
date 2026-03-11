# SPDX-License-Identifier: GPL-3.0
#
# Functions:
# - VDSO_NAME=[linux-vdso.so.1]
# - gen_vdso_elf()
#
ifndef _VDSO_MK
_VDSO_MK = 1

VDSO_ROOT := $(shell realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/../vdso/)

# kernel command line 'vdso=0' could disable vDSO
CMDLINE_VDSO := $(shell grep -o vdso=0 /proc/cmdline)

# see vdso(7)
VDSO_NAME := linux-vdso.so.1
VDSO_NAME_AARCH64 = linux-vdso.so.1
VDSO_NAME_ARM = linux-vdso.so.1
VDSO_NAME_X86_64 = linux-vdso.so.1
VDSO_NAME_X86_32 = linux-vdso.so.1

KVDSO64 :=

ifeq ($(shell uname -m),x86_64)
  VDSO_NAME := ${VDSO_NAME_X86_64}
  KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso64.so
else ifeq ($(shell uname -m),aarch64)
  VDSO_NAME := ${VDSO_NAME_AARCH64}
  KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso.so
endif

# $1 - vdso name
define gen_vdso_elf
${Q}$(VDSO_ROOT)/dump.sh -s -n $1
endef

ifeq ($(wildcard $(KVDSO64)),)
  $(warning "WARNING: Not found ${KVDSO64}, use dump")
  KVDSO64 := ${VDSO_NAME}
endif

ifdef DEBUG
  $(info CMDLINE_VDSO=${CMDLINE_VDSO})
  $(info VDSO_ROOT ${VDSO_ROOT})
  $(info VDSO_NAME ${VDSO_NAME})
endif

endif

# SPDX-License-Identifier: GPL-3.0
#
# Functions:
# - VDSO_NAME=[linux-vdso.so.1]
# - VDSO_CFLAGS=
# - gen_vdso_elf()
#
ifndef _VDSO_MK
_VDSO_MK = 1

VDSO_CFLAGS :=
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

ifeq ($(wildcard $(KVDSO64)),)
  $(warning "WARNING: Not found ${KVDSO64}, use dump")
  KVDSO64 := ${VDSO_NAME}
endif

VDSO_CFLAGS += -nolibc

ifeq ($(shell uname -m),x86_64)
  # See linux:/arch/x86/entry/vdso/Makefile
  VDSO_CFLAGS += -P -C --shared -Wl,-melf_x86_64
  VDSO_CFLAGS += -Wl,-soname=${VDSO_NAME}.custom
  VDSO_CFLAGS += -Wl,-shared -Wl,--hash-style=both -Wl,--build-id=sha1 -Wl,--no-undefined
  VDSO_CFLAGS += -Wl,-Bsymbolic -Wl,-znoexecstack
  VDSO_CFLAGS += -Wl,--no-undefined -Wl,-zmax-page-size=4096
  VDSO_CFLAGS += -mcmodel=small -fPIC -O2 -fasynchronous-unwind-tables -m64
  VDSO_CFLAGS += -fno-stack-protector -fno-omit-frame-pointer -foptimize-sibling-calls
else ifeq ($(shell uname -m),aarch64)
  # See linux:/arch/arm64/kernel/vdso/Makefile
  VDSO_CFLAGS += -shared
  VDSO_CFLAGS += -Wl,-soname=${VDSO_NAME}.custom
  VDSO_CFLAGS += -Wl,-Bsymbolic -Wl,--build-id=sha1
  VDSO_CFLAGS += -fno-common -fno-builtin -fno-stack-protector -ffixed-x18
  VDSO_CFLAGS += -O2 -mcmodel=tiny -fasynchronous-unwind-tables
else
  $(warning Not support $(shell uname -m) yet)
endif

# $1 - vdso name
define gen_vdso_elf
${Q}$(VDSO_ROOT)/dump.sh -s -n $1
endef

ifdef DEBUG
  $(info CMDLINE_VDSO=${CMDLINE_VDSO})
  $(info VDSO_ROOT ${VDSO_ROOT})
  $(info VDSO_NAME ${VDSO_NAME})
endif

endif

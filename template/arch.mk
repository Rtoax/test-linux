# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - cflags-arch=
#
# - CPU_ARCH=[x86_64|aarch64|sw_64|loongarch64|riscv64|...]
# - LINUX_SUBARCH=[x86|arm64|...]
# - IS_X86_64=[y]
# - IS_AARCH64=[y]
# - IS_LOONGARCH64=[y]
# - IS_RISCV64=[y]
# - IS_SW_64=[y]
# - IS_S390X=[y]
#
ifndef _ARCH_MK
_ARCH_MK = 1

CPU_ARCH := $(shell uname -m)
cflags-arch :=

ifeq (${CPU_ARCH},x86_64)
  export IS_X86_64 := y
else ifeq (${CPU_ARCH},aarch64)
  export IS_AARCH64 := y
else ifeq (${CPU_ARCH},sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    cflags-arch += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    cflags-arch += -mcpu=sw6b
  endif
  export IS_SW_64 := y
else ifeq (${CPU_ARCH},loongarch64)
  export IS_LOONGARCH64 := y
else ifeq (${CPU_ARCH},riscv64)
  export IS_RISCV64 := y
else ifeq (${CPU_ARCH},s390x)
  export IS_S390X := y
else
  $(error Not support ${CPU_ARCH})
endif

# see linux scripts/subarch.include
LINUX_SUBARCH := $(shell uname -m | sed -e s/i.86/x86/ -e s/x86_64/x86/ \
					-e s/sun4u/sparc64/ \
					-e /^arm64$$/!s/arm.*/arm/ -e s/sa110/arm/ \
					-e s/s390x/s390/ \
					-e s/ppc.*/powerpc/ -e s/mips.*/mips/ \
					-e s/sh[234].*/sh/ -e s/aarch64.*/arm64/ \
					-e s/riscv.*/riscv/ -e s/loongarch.*/loongarch/)

ifdef DEBUG
  $(info CPU_ARCH = ${CPU_ARCH})
  $(info LINUX_SUBARCH = ${LINUX_SUBARCH})
  $(info cflags-arch = ${cflags-arch})
endif

export CPU_ARCH
export cflags-arch
export LINUX_SUBARCH

endif

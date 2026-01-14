# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - cflags-arch=
#
# - IS_X86_64=y
# - IS_AARCH64=y
# - IS_LOONGARCH64=y
# - IS_RISCV64=y
# - IS_SW_64=y
#
ifndef _ARCH_MK
_ARCH_MK = 1

cflags-arch :=

ifeq ($(shell uname -m),x86_64)
  export IS_X86_64 := y
else ifeq ($(shell uname -m),aarch64)
  export IS_AARCH64 := y
else ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    cflags-arch += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    cflags-arch += -mcpu=sw6b
  endif
  export IS_SW_64 := y
else ifeq ($(shell uname -m),loongarch64)
  export IS_LOONGARCH64 := y
else ifeq ($(shell uname -m),riscv64)
  export IS_RISCV64 := y
endif

export cflags-arch

endif

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - CFLAGS_ARCH=
#
# - IS_X86_64=y
# - IS_AARCH64=y
# - IS_LOONGARCH64=y
# - IS_RISCV64=y
# - IS_SW_64=y
#
_ARCH_MK = 1

CFLAGS_ARCH :=

ifeq ($(shell uname -m),x86_64)
  IS_X86_64 := y
  export IS_X86_64
else ifeq ($(shell uname -m),aarch64)
  IS_AARCH64 := y
  export IS_AARCH64
else ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    CFLAGS_ARCH += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    CFLAGS_ARCH += -mcpu=sw6b
  endif
  IS_SW_64 := y
  export IS_SW_64
else ifeq ($(shell uname -m),loongarch64)
  IS_LOONGARCH64 := y
  export IS_LOONGARCH64
else ifeq ($(shell uname -m),riscv64)
  IS_RISCV64 := y
  export IS_RISCV64
endif

export CFLAGS_ARCH

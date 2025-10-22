# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Output definitions:
# - CFLAGS_ARCH=
# - IS_X86_64=y
# - IS_AARCH64=y

_ARCH = 1

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
endif

export CFLAGS_ARCH

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Exports:
# - HAVE_LIBKMOD=[y|n]
# - KDIR=
#
ifndef _KMOD_MK
_KMOD_MK = 1

include define.mk

KDIR :=
KDIR1 := /lib/modules/$(shell uname -r)/build/
KDIR2 := /usr/src/linux-headers-$(shell uname -r)/

ifeq ($(wildcard ${KDIR1}),)
  $(warning Not found ${KDIR1}, skipping)
  ifeq ($(wildcard ${KDIR2}),)
    $(warning Not found ${KDIR2}, skipping)
  else
    KDIR := ${KDIR2}
  endif
else
  KDIR := ${KDIR1}
endif

$(call check_file_and_def,/usr/include/libkmod.h,HAVE_LIBKMOD)

ifdef DEBUG
  $(info KDIR = ${KDIR})
endif

export KDIR

endif

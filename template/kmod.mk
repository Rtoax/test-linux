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

KDIR := /lib/modules/$(shell uname -r)/build/

ifeq ($(wildcard ${KDIR}),)
  $(warning Not found ${KDIR}, skipping)
else
  export KDIR
endif

$(call check_file_and_def,/usr/include/libkmod.h,HAVE_LIBKMOD)

endif

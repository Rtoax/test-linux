# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Exports:
# - KDIR=
#
ifndef _KMOD_MK
_KMOD_MK = 1

KDIR := /lib/modules/$(shell uname -r)/build/

ifeq ($(wildcard ${KDIR}),)
  ifndef __IGNORE_NOTFOUND_ERROR__
    $(error Not found ${KDIR}, install kernel development package first)
  else
    $(warning Not found ${KDIR}, skipping)
  endif
else
  export KDIR
endif

endif

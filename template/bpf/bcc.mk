# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BCC=[y|n]
# - LIBBCC_PATH=[/lib64/libbcc.so.0]
# - bcc-cflags=
# - bcc-ldflags=
#
ifndef _BPF_BCC_MK
_BPF_BCC_MK = 1

include ldconfig.mk

LIBBCC_PATH := $(shell ${LDCONFIG} -p | grep libbcc.so 2>/dev/null | awk '{print $$NF}' | head -1)
BCC_SYMS_HDR := /usr/include/bcc/bcc_syms.h

ifeq ($(LIBBCC_PATH),)
  export HAVE_BCC := n
else

  bcc-cflags := -DHAVE_BCC=1
  bcc-ldflags := -lbcc

  export HAVE_BCC := y
  export LIBBCC_PATH := $(shell realpath ${LIBBCC_PATH})
  export bcc-cflags bcc-ldflags

endif # end of Found BCC

ifdef DEBUG
  $(info HAVE_BCC = ${HAVE_BCC})
  $(info LIBBCC_PATH = ${LIBBCC_PATH})
  $(info bcc-cflags = ${bcc-cflags})
  $(info bcc-ldflags = ${bcc-ldflags})
endif

endif

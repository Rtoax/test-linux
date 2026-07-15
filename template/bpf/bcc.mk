# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BCC=[y|n]
# - LIBBCC_PATH=[/lib64/libbcc.so.0]
# - HAVE_BCC_HDR=[y]
# - bcc-cflags=
# - bcc-ldflags=
#
ifndef _BPF_BCC_MK
_BPF_BCC_MK = 1

include ldconfig.mk
include define.mk

LIBBCC_PATH := $(call find_library_path,libbcc.so)
BCC_SYMS_HDR := /usr/include/bcc/bcc_syms.h

ifeq ($(LIBBCC_PATH),)
  export HAVE_BCC := n
else

  $(call check_file_and_def,${BCC_SYMS_HDR},HAVE_BCC_HDR)

  bcc-cflags := -DHAVE_BCC=1
  ifeq (${HAVE_BCC_HDR},y)
    bcc-cflags += -DHAVE_BCC_HDR=1
  endif
  bcc-ldflags := -lbcc

  export HAVE_BCC := y
  export LIBBCC_PATH := $(shell realpath ${LIBBCC_PATH})
  export bcc-cflags bcc-ldflags

endif # end of Found BCC

ifdef DEBUG
  $(info HAVE_BCC = ${HAVE_BCC})
  $(info LIBBCC_PATH = ${LIBBCC_PATH})
  $(info BCC_SYMS_HDR = ${BCC_SYMS_HDR})
  $(info bcc-cflags = ${bcc-cflags})
  $(info bcc-ldflags = ${bcc-ldflags})
endif

endif

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - HAVE_BCC=
# - LIBBCC_PATH=
# - bcc-cflags=
# - bcc-ldflags=
#
_BCC = 1

LIBBCC_PATH := $(shell ldconfig -p | grep libbcc.so 2>/dev/null | awk '{print $$NF}' | head -1)
LIBBCC_PATH := $(shell realpath ${LIBBCC_PATH})

ifneq ($(LIBBCC_PATH),)
  bcc-cflags := -DHAVE_BCC=1
  bcc-ldflags := -lbcc
  HAVE_BCC := y
  export HAVE_BCC
  export bcc-cflags bcc-ldflags
endif

ifdef DEBUG
  $(info HAVE_BCC = ${HAVE_BCC})
  $(info LIBBCC_PATH = ${LIBBCC_PATH})
  $(info bcc-cflags = ${bcc-cflags})
  $(info bcc-ldflags = ${bcc-ldflags})
endif

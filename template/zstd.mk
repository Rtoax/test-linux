# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
# https://github.com/facebook/zstd
#
# Definitions:
# - ZSTD=[/usr/bin/zstd]
# - HAVE_ZSTD=[y|n]
#
ifndef _ZSTD_MK
_ZSTD_MK = 1

ZSTD := $(shell which zstd 2>/dev/null || true)
ifeq ($(ZSTD),)
  HAVE_ZSTD := n
else
  HAVE_ZSTD := y
endif

ifdef DEBUG
  $(info ZSTD = ${ZSTD})
  $(info HAVE_ZSTD = ${HAVE_ZSTD})
endif

ifeq ($(ZSTD),)
  $(error "Not found zstd in anywhere, install first")
endif

export ZSTD HAVE_ZSTD

endif

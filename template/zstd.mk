# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
# https://github.com/facebook/zstd
#
# Definitions:
# - ZSTD=[/usr/bin/zstd]
# - HAVE_ZSTD=[y|n]
# - HAVE_LIBZSTD=[y|n]
#
ifndef _ZSTD_MK
_ZSTD_MK = 1

include ldconfig.mk
include define.mk

$(call find_cmd_and_def,zstd)

HAVE_LIBZSTD := $(call have_library,libzstd.so)

ifdef DEBUG
  $(info ZSTD = ${ZSTD})
  $(info HAVE_ZSTD = ${HAVE_ZSTD})
  $(info HAVE_LIBZSTD = ${HAVE_LIBZSTD})
endif

ifeq ($(ZSTD),)
  $(error "Not found zstd in anywhere, install first")
endif

export ZSTD
export HAVE_ZSTD
export HAVE_LIBZSTD

endif

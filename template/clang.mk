# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_CLANG=[y|n]
# - CLANG=[/usr/bin/clang]
# - CLANGXX=[/usr/bin/clang++]
#
# Functions:
#
ifndef _CLANG_MK
_CLANG_MK = 1

include shell.mk
include define.mk

$(call find_cmd_and_def,clang)

CLANGXX := $(shell which clang++ 2>/dev/null)

CC ?= ${CLANG}
CXX ?= ${CLANGXX}

ifdef DEBUG
  $(info CLANGXX = ${CLANGXX})
endif

export CLANGXX

ifeq ($(CLANG),)
  $(warning Not found clang, please install clang first)
endif

endif # end of _CLANG_MK

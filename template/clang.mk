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
$(call find_cmd_and_def,clang++,clangxx)

CC ?= ${CLANG}
CXX ?= ${CLANGXX}

ifeq ($(CLANG),)
  $(warning Not found clang, please install clang first)
endif

endif # end of _CLANG_MK

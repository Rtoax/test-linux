# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_CLANG=[y|n]
# - HAVE_CLANGXX=[y|n]
# - CLANG=[/usr/bin/clang]
# - CLANGXX=[/usr/bin/clang++]
# - CLANG_MACHINE=[x86_64-pc-linux-gnu]
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

CLANG_MACHINE := $(shell ${CLANG} -dumpmachine)

ifeq ($(CLANG),)
  $(warning Not found clang, please install clang first)
endif

ifdef DEBUG
  $(info CLANG_MACHINE = ${CLANG_MACHINE})
endif

endif # end of _CLANG_MK

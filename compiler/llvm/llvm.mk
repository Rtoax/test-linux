# SPDX-License-Identifier: GPL-3.0

LLVM_CONFIG := $(shell which llvm-config 2>/dev/null)
ifeq ($(LLVM_CONFIG),)
  $(warning Not found llvm-config, please install llvm first)
endif

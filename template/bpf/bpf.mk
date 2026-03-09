# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
# Output definitions:
# - BPF_TARGET_ARCH=
# - CFLAG_BPF_TARGET_ARCH=
#
ifndef _BPF_BPF_MK
_BPF_BPF_MK = 1

BPF_TARGET_ARCH := $(shell uname -m | sed 's/x86_64/x86/' \
			 | sed 's/arm.*/arm/' \
			 | sed 's/aarch64/arm64/' \
			 | sed 's/ppc64le/powerpc/' \
			 | sed 's/mips.*/mips/' \
			 | sed 's/riscv64/riscv/' \
			 | sed 's/loongarch64/loongarch/')
ifeq (${BPF_TARGET_ARCH},$(shell uname -m))
  $(error Not handle arch ${shell uname -m} yet, please do)
endif

CFLAG_BPF_TARGET_ARCH := -D__TARGET_ARCH_$(BPF_TARGET_ARCH)

ifdef DEBUG
  $(info BPF_TARGET_ARCH = ${BPF_TARGET_ARCH})
  $(info CFLAG_BPF_TARGET_ARCH = ${CFLAG_BPF_TARGET_ARCH})
endif

endif

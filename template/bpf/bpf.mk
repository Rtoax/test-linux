# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao
#
# Output definitions:
# - BPFFS=[/sys/fs/bpf/]
# - BPF_TARGET_ARCH=
# - bpf-cflags=
#
ifndef _BPF_BPF_MK
_BPF_BPF_MK = 1

BPFFS := /sys/fs/bpf/
bpf-cflags :=

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

bpf-cflags += -D__TARGET_ARCH_$(BPF_TARGET_ARCH)

export BPFFS
export BPF_TARGET_ARCH
export bpf-cflags

ifdef DEBUG
  $(info BPFFS = ${BPFFS})
  $(info BPF_TARGET_ARCH = ${BPF_TARGET_ARCH})
  $(info bpf-cflags = ${bpf-cflags})
endif

endif

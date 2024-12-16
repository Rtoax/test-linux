# SPDX-License-Identifier: GPL-3.0
#
BPF_TARGET_ARCH ?= $(shell uname -m | sed 's/x86_64/x86/' \
			 | sed 's/arm.*/arm/' \
			 | sed 's/aarch64/arm64/' \
			 | sed 's/ppc64le/powerpc/' \
			 | sed 's/mips.*/mips/' \
			 | sed 's/riscv64/riscv/' \
			 | sed 's/loongarch64/loongarch/')

CFLAG_BPF_TARGET_ARCH := -D__TARGET_ARCH_$(BPF_TARGET_ARCH)


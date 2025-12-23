# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - CPU_HAVE_AVX2=y
# - CPU_HAVE_AVX512F=y
#
_CPU_FEATURE = 1

CPU_HAVE_AVX2 := $(shell lscpu | grep -wo avx512f >/dev/null && echo y)
CPU_HAVE_AVX512F := $(shell lscpu | grep -wo avx512f >/dev/null && echo y)

ifdef DEBUG
  $(info CPU_HAVE_AVX512F = ${CPU_HAVE_AVX512F})
  $(info CPU_HAVE_AVX2 = ${CPU_HAVE_AVX2})
endif

export CPU_HAVE_AVX2
export CPU_HAVE_AVX512F

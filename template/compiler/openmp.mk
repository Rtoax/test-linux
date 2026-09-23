# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
ifndef _COMPILER_OPENMP_MK
_COMPILER_OPENMP_MK = 1

OPENMP_VERSION := $(shell cc -fopenmp -dM -E - < /dev/null | grep -Po '_OPENMP \K[0-9]+$$')

ifdef DEBUG
  $(info OPENMP_VERSION = ${OPENMP_VERSION})
endif

endif

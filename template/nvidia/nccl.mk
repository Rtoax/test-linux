# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - CUDA_ROOT=
#
# Output definitions:
# - HAVE_NCCL=[y]
# - nccl-cflags=
# - nccl-ldflags=
#
ifndef _NVIDIA_NCCL_MK
_NVIDIA_NCCL_MK = 1

include define.mk
include nvidia/cuda.mk

$(call check_file_and_def,/usr/include/nccl.h,HAVE_NCCL)
ifndef (${HAVE_NCCL},y)
  $(call check_file_and_def,${CUDA_ROOT}/include/nccl.h,HAVE_NCCL)
endif

$(if ${HAVE_NCCL}, $(eval nccl-cflags += -DHAVE_NCCL=1))
$(if ${HAVE_NCCL}, $(eval nccl-ldflags += -lnccl))

ifdef DEBUG
  $(info HAVE_NCCL = ${HAVE_NCCL})
  $(info nccl-cflags = ${nccl-cflags})
  $(info nccl-ldflags = ${nccl-ldflags})
endif

export nccl-cflags
export nccl-ldflags

endif

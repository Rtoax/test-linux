# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_NCCL=[y]
#
ifndef _NVIDIA_NCCL_MK
_NVIDIA_NCCL_MK = 1

include define.mk
include nvidia/cuda.mk

$(call check_file_and_def,${CUDA_ROOT}/include/nccl.h,HAVE_NCCL)

ifdef DEBUG
  $(info HAVE_NCCL = ${HAVE_NCCL})
endif

endif

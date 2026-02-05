# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_NVIDIA_GPU=[y|n]
#
ifndef _NVIDIA_NCCL_MK
_NVIDIA_NCCL_MK = 1

HAVE_NVIDIA_GPU := n

# Your system has Nvidia GPU card
ifneq ($(shell lspci | grep -oi nvidia),)
  HAVE_NVIDIA_GPU := y
endif

ifdef DEBUG
  $(info HAVE_NVIDIA_GPU = ${HAVE_NVIDIA_GPU})
endif

export HAVE_NVIDIA_GPU

endif

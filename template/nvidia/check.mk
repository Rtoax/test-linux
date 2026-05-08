# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - nvcc_check()=[y]
#
ifndef _NVIDIA_CHECK_MK
_NVIDIA_CHECK_MK = 1

include nvidia/cuda.mk

# Check nvcc support option or not
define nvcc_check
$(shell printf '#include <cuda_runtime.h>\nint main(void) { return 0; }' | \
  ${NVCC} -x c - -o /dev/null >/dev/null 2>&1 \
    && echo y)
endef

ifneq (${NVCC},)
  ifneq ($(call nvcc_check),y)
    $(error nvcc_check failed)
  endif
endif

endif # _NVIDIA_CHECK_MK

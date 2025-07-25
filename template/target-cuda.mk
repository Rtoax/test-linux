# SPDX-License-Identifier: GPL-3.0
NVCC := $(shell which nvcc 2>/dev/null)
# see https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
CUDA_NVCC_123 := /usr/local/cuda-12.3/bin/nvcc
CUDA_NVCC_129 := /usr/local/cuda-12.9/bin/nvcc

ifeq ($(NVCC),)
  ifneq ($(wildcard ${CUDA_NVCC_129}),)
    NVCC := ${CUDA_NVCC_129}
  else ifneq ($(wildcard ${CUDA_NVCC_123}),)
    NVCC := ${CUDA_NVCC_123}
  endif
endif
ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -Wno-deprecated-gpu-targets

ifdef DEBUG
  $(info NVCC = ${NVCC})
  $(info CFLAGS_NVCC = ${CFLAGS_NVCC})
  $(info LDFLAGS_NVCC = ${LDFLAGS_NVCC})
endif

# NOTE: NVCC's cflags,ldflags is totally different from gcc/clang, thus, we
# don't use CFLAGS and LDFLAGS.
${OUTPUT}%.cu.o: %.cu | ${OUTPUT}
	$(call log_tgt_obj,NVCC,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.E.cu: %.cu | ${OUTPUT}
	$(call log_tgt_obj,NVCC E,$(<),$(@))
	${Q}$(NVCC) -E -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

$(targets-nvcc): %:
	$(call log_tgt_exe,NVCC LD,$(<),$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS_NVCC) $(LDFLAGS_NVCC_$(*))

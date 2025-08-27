# SPDX-License-Identifier: GPL-3.0
NVCC := $(shell which nvcc 2>/dev/null)
CUOBJDUMP := $(shell which cuobjdump 2>/dev/null)
NVDISASM := $(shell which nvdisasm 2>/dev/null)

# see https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
# see https://developer.nvidia.com/cuda-downloads
CUDA_NVCC_130 := /usr/local/cuda-13.0/bin/nvcc
CUDA_NVCC_123 := /usr/local/cuda-12.3/bin/nvcc
CUDA_NVCC_129 := /usr/local/cuda-12.9/bin/nvcc
CUDA_NVCC := /usr/local/cuda/bin/nvcc

ifeq ($(NVCC),)
  ifneq ($(wildcard ${CUDA_NVCC_130}),)
    NVCC := ${CUDA_NVCC_130}
  else ifneq ($(wildcard ${CUDA_NVCC_129}),)
    NVCC := ${CUDA_NVCC_129}
  else ifneq ($(wildcard ${CUDA_NVCC_123}),)
    NVCC := ${CUDA_NVCC_123}
  else ifneq ($(wildcard ${CUDA_NVCC}),)
    NVCC := ${CUDA_NVCC}
  endif
endif
ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

# NVCC: --gpu-architecture
# Pascal (sm_60+)
# Volta (sm_70+)
# Turing (sm_75+)
# Ampere (sm_80+)
# Ada Lovelace (sm_89+)
# Hopper (sm_90+)
CFLAGS_NVCC += -arch=sm_80
LDFLAGS_NVCC += -arch=sm_80

CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -Wno-deprecated-gpu-targets

ifdef DEBUG
  CFLAGS_NVCC += -DDEBUG=${DEBUG}
  $(info $(shell ${NVCC} --version))
  $(info NVCC = ${NVCC})
  $(info NVCC VERSION: $(shell ${NVCC} --version))
  $(info CFLAGS_NVCC = ${CFLAGS_NVCC})
  $(info LDFLAGS_NVCC = ${LDFLAGS_NVCC})
endif

ifdef ERROR
  CFLAGS_NVCC += -DERROR=1
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

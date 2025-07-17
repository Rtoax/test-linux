# SPDX-License-Identifier: GPL-3.0
NVCC := $(shell which nvcc 2>/dev/null)
# see https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
CUDA_NVCC_129 := /usr/local/cuda-12.9/bin/nvcc

ifeq ($(NVCC),)
  ifneq ($(wildcard ${CUDA_NVCC_129}),)
    NVCC := ${CUDA_NVCC_129}
  endif
endif
ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

# Fix errors, those cflags added in main.mk
# nvcc fatal   : Value '-Wall' is not defined for option 'Werror'
# nvcc fatal   : Unknown option '-Wall'
# nvcc fatal   : Unknown option '-Wstrict-prototypes'
CFLAGS := $(patsubst -Wall,,${CFLAGS})
CFLAGS := $(patsubst -Werror,,${CFLAGS})
CFLAGS := $(patsubst -Wstrict-prototypes,,${CFLAGS})
LDFLAGS := $(patsubst -Wall,,${LDFLAGS})
LDFLAGS := $(patsubst -Werror,,${LDFLAGS})

ifdef DEBUG
  $(info NVCC = ${NVCC})
endif

%.cu.o: %.cu
	$(call log_tgt_obj,NVCC,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_NVCC): %:
	$(call log_tgt_exe,NVCC LD,$(<),$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# This makefile use to compile Nvidia targets.
#
# Targets list:
# - .cu.o
# - .cu.so.o
# - .cu.a.o
# - .cu.ptx
# - .cu.cpp.ii
# - .cu.cubin
# - .cu.fatbin
# - .nv_fatbin
# - .nvFatBinSegment
# - .cu.ptx.dump
# - .cu.sass.dump
# - .E.cu
# - target-nvcc-y
# - target-nvcc-libso-y
# - target-nvcc-liba-y
#
# Input definitions:
# - HAVE_NCCL
# - HAVE_CUDNN
# - HAVE_CUFILE
# - HAVE_CUPTI
# - HAVE_NVRTC
# - HAVE_NVIDIA_GPU
#
ifndef _TARGET_NVIDIA_MK
_TARGET_NVIDIA_MK = 1

include dir.mk
include nvidia/cuda.mk
include nvidia/device.mk
include nvidia/nccl.mk

cflags-nvcc-cubin := --cubin
cflags-nvcc-fatbin := --fatbin
cflags-nvcc-so := -Xcompiler -fPIC
ldflags-nvcc-so := -shared -Xcompiler -fPIC

CFLAGS_NVCC += -I${TOPDIR}/hpc/nvidia/cuda/
CFLAGS_NVCC += -DHAVE_CUDA=1
ifdef HAVE_NCCL
  CFLAGS_NVCC += -DHAVE_NCCL=1
endif
ifdef HAVE_CUDNN
  CFLAGS_NVCC += -DHAVE_CUDNN=1
endif
ifdef HAVE_CUFILE
  CFLAGS_NVCC += -DHAVE_CUFILE=1
endif
ifdef HAVE_CUPTI
  CFLAGS_NVCC += -DHAVE_CUPTI=1
endif
ifdef HAVE_NVRTC
  CFLAGS_NVCC += -DHAVE_NVRTC=1
endif
CFLAGS_NVCC += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
CFLAGS_NVCC += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
CFLAGS_NVCC += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}

ifeq (${HAVE_NVIDIA_GPU},y)
  CFLAGS_NVCC += -arch=native
  LDFLAGS_NVCC += -arch=native
else
  CFLAGS_NVCC += -arch=sm_80
  LDFLAGS_NVCC += -arch=sm_80
endif

# Use to test fakeCUDA
ldflags-cudart := --cudart shared

CFLAGS_NVCC += -std=c++17
CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -lcublas -lcublasLt
LDFLAGS_NVCC += -lcuda
LDFLAGS_NVCC += -lcufft
LDFLAGS_NVCC += -lcurand
LDFLAGS_NVCC += -lcusparse
LDFLAGS_NVCC += -lcusolver
ifdef HAVE_NCCL
  LDFLAGS_NVCC += -lnccl
endif
ifdef HAVE_CUDNN
  LDFLAGS_NVCC += -lcudnn
endif
ifdef HAVE_CUFILE
  LDFLAGS_NVCC += -lcufile
endif
ifdef HAVE_CUPTI
  LDFLAGS_NVCC += -lcupti
endif
ifdef HAVE_NVRTC
  LDFLAGS_NVCC += -lnvrtc
endif
LDFLAGS_NVCC += ${ldflags-cudart}

ifdef ERROR
  CFLAGS_NVCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_NVCC += -DDEBUG=${DEBUG}
endif

CFLAGS_NVCC_SO += ${CFLAGS_NVCC}
CFLAGS_NVCC_SO += ${cflags-nvcc-so}
LDFLAGS_NVCC_SO += ${LDFLAGS_NVCC}
LDFLAGS_NVCC_SO += ${ldflags-nvcc-so}

CFLAGS_NVCC_A += ${CFLAGS_NVCC_SO}

ifdef DEBUG
  $(info cflags-nvcc-cubin = ${cflags-nvcc-cubin})
  $(info cflags-nvcc-fatbin = ${cflags-nvcc-fatbin})
  $(info CFLAGS_NVCC = ${CFLAGS_NVCC})
  $(info LDFLAGS_NVCC = ${LDFLAGS_NVCC})
  $(info CFLAGS_NVCC_SO = ${CFLAGS_NVCC_SO})
  $(info LDFLAGS_NVCC_SO = ${LDFLAGS_NVCC_SO})
  $(info CFLAGS_NVCC_A = ${CFLAGS_NVCC_A})
  $(info target-nvcc-y = ${target-nvcc-y})
endif

# NOTE: NVCC's cflags,ldflags is totally different from gcc/clang, thus, we
# don't use CFLAGS and LDFLAGS.
${OUTPUT}%.cu.o: %.cu | ${OUTPUT}
	$(call log_obj,NVCC,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.ptx: %.cu | ${OUTPUT}
	$(call log_obj,NVCC PTX,$(<),$(@))
	${Q}$(NVCC) -ptx -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.cpp.ii: %.cu | ${OUTPUT}
	$(call log_obj,NVCC II,$(<),$(@))
	${Q}$(NVCC) -cuda -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.cubin: %.cu | ${OUTPUT}
	$(call log_obj,NVCC CUBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-cubin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.fatbin: %.cu | ${OUTPUT}
	$(call log_obj,NVCC FATBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-fatbin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

# Example format of nv_fatbin and nvFatBinSegment, see:
# commit 0f8f83ac8109 ("targets/nvidia.mk: add .nv_fatbin and .nvFatBinSegment targets")
${OUTPUT}%.nv_fatbin: % | ${OUTPUT}
	$(call log_obj,CUDA FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.nv_fatbin $(<) $(@)

${OUTPUT}%.nvFatBinSegment: % | ${OUTPUT}
	$(call log_obj,CUDA FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.nvFatBinSegment $(<) $(@)

${OUTPUT}%.cu.sass.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_obj,CUDA SASS,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-sass $(<) > ${@}

${OUTPUT}%.cu.ptx.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_obj,CUDA PTX,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-ptx $(<) > ${@}

${OUTPUT}%.E.cu: %.cu | ${OUTPUT}
	$(call log_obj,NVCC E,$(<),$(@))
	${Q}$(NVCC) -E -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.so.o: %.cu | ${OUTPUT}
	$(call log_obj,NVCC SO.o,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS_NVCC_SO) $(CFLAGS_NVCC_SO_$(*))

${OUTPUT}%.cu.a.o: %.cu | ${OUTPUT}
	$(call log_obj,NVCC A.o,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS_NVCC_A) $(CFLAGS_NVCC_A_$(*))

$(target-nvcc-y): %:
	$(call log_tgt,NVCC LD,$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS_NVCC) $(LDFLAGS_NVCC_$(*))

$(target-nvcc-libso-y): %:
	$(call log_tgt,NVCC SO,$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS_NVCC_SO) $(LDFLAGS_NVCC_SO$(*))

$(target-nvcc-liba-y): %:
	$(call log_tgt,NVCC AR,$(@))
	${Q}ar rcs $(@) $(^)

endif

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_CUDA=y
# - HAVE_NCCL=y
# - HAVE_CUDNN=y
# - HAVE_CUFILE=y	GPUDirect Storage
# - HAVE_CUPTI=y	CUDA Profiling Tools Interface
# - NVCC=
# - CUOBJDUMP=
# - NVDISASM=
# - CUDA_ROOT=[/usr/local/cuda/,/usr/]
# - CUDA_VERSION_CODE=
# - CUDA_VERSION_MAJOR=[0]
# - CUDA_VERSION_MINOR=[0]
# - CUDA_VERSION_PATCH=[0]
#
# Modify definitions:
# - target-nvcc-y
# - target-nvcc-liba-y
# - target-nvcc-libso-y
#
ifndef _GPU_CUDA_MK
_GPU_CUDA_MK = 1

include define.mk

NVCC := $(shell which nvcc 2>/dev/null)
CUOBJDUMP := $(shell which cuobjdump 2>/dev/null)
NVDISASM := $(shell which nvdisasm 2>/dev/null)

# After install CUDA, the /usr/local/cuda/ is symlink.
# refs
# - https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
# - https://developer.nvidia.com/cuda-downloads
CUDA_ROOT := /usr/local/cuda/

ifneq ($(wildcard ${CUDA_ROOT}),)
  CUDA_ROOT := $(shell realpath ${CUDA_ROOT})
else
  ifneq ($(wildcard /usr/include/cuda.h),)
    CUDA_ROOT := /usr/
  else
    # Not found cuda in anywhere
    CUDA_ROOT :=
  endif
endif

# Use env's nvcc first
ifeq ($(NVCC),)
  ifneq (${CUDA_ROOT},)
    NVCC := ${CUDA_ROOT}/bin/nvcc
    CUOBJDUMP := ${CUDA_ROOT}/bin/cuobjdump
  endif
else
  NVCC := $(shell realpath ${NVCC})
  CUOBJDUMP := $(shell realpath ${CUOBJDUMP})
endif

# If not found NVCC
ifeq ($(wildcard $(NVCC)),)
  ifneq ($(target-nvcc-y)$(target-nvcc-libs-y)$(target-nvcc-libso-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found nvcc with target nvcc not empty, but __IGNORE_NOTFOUND_ERROR__)
    else
      $(error Not found nvcc with target nvcc not empty, install cuda first)
    endif
  else
    $(warning Although not found nvcc, but you don't have target nvcc)
  endif

  NVCC :=
  CUOBJDUMP :=
  NVDISASM :=
  CUDA_VERSION_MAJOR := 0
  CUDA_VERSION_MINOR := 0
  CUDA_VERSION_PATCH := 0
# Found NVCC
else
  CUDA_VERSION_RAW := $(shell ${NVCC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)
  ifeq (${CUDA_VERSION_RAW},)
    $(error Not found CUDA Version in ${NVCC} --version)
  endif

  CUDA_VERSION_MAJOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$1}')
  CUDA_VERSION_MINOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$2}')
  CUDA_VERSION_PATCH := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$3}')

  ifndef HAVE_CUDA
    export HAVE_CUDA := y
  endif
endif

CUDA_VERSION_CODE := $(shell echo "$$(( (${CUDA_VERSION_MAJOR}*1000) + \
					(${CUDA_VERSION_MINOR}*10) ))" )

$(call check_file_and_def,${CUDA_ROOT}/include/nccl.h,HAVE_NCCL)
$(call check_file_and_def,${CUDA_ROOT}/include/cudnn.h,HAVE_CUDNN)
$(call check_file_and_def,${CUDA_ROOT}/include/cupti.h,HAVE_CUPTI)
$(call check_file_and_def,${CUDA_ROOT}/include/cufile.h,HAVE_CUFILE)

ifdef DEBUG
  $(info HAVE_CUDA = ${HAVE_CUDA})
  ifneq (${NVCC},)
    $(info NVCC Version $(shell ${NVCC} --version))
  endif
  $(info NVCC = ${NVCC})
  $(info CUDA_VERSION_CODE = ${CUDA_VERSION_CODE})
  $(info CUDA_VERSION_MAJOR = ${CUDA_VERSION_MAJOR})
  $(info CUDA_VERSION_MINOR = ${CUDA_VERSION_MINOR})
  $(info CUDA_VERSION_PATCH = ${CUDA_VERSION_PATCH})
endif

export NVCC CUOBJDUMP NVDISASM CUDA_ROOT
export CUDA_VERSION_MAJOR CUDA_VERSION_MINOR CUDA_VERSION_PATCH

endif

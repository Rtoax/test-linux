# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_CUDA
# - HAVE_NCCL
# - NVCC
# - CUOBJDUMP
# - NVDISASM
# - CUDA_ROOT
# - CUDA_VERSION_MAJOR
# - CUDA_VERSION_MINOR
# - CUDA_VERSION_PATCH

_CUDA = 1

NCCL_H := /usr/include/nccl.h

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
  CUDA_ROOT :=
endif

ifeq ($(NVCC),)
  ifneq ($(wildcard ${CUDA_ROOT}),)
    NVCC := ${CUDA_ROOT}/bin/nvcc
    CUOBJDUMP := ${CUDA_ROOT}/bin/cuobjdump
  endif
else
  NVCC := $(shell realpath ${NVCC})
  CUOBJDUMP := $(shell realpath ${CUOBJDUMP})
endif

# If not found NVCC
ifeq ($(wildcard $(NVCC)),)
  ifneq ($(target-nvcc-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found nvcc with target-nvcc-y not empty, but __IGNORE_NOTFOUND_ERROR__)
    else
      $(error Not found nvcc with target-nvcc-y not empty, install cuda first)
    endif
  else
    $(warning Although not found nvcc, but you don't have target-nvcc-y)
  endif

  NVCC :=
  CUOBJDUMP :=
  NVDISASM :=
  CUDA_VERSION_MAJOR :=
  CUDA_VERSION_MINOR :=
  CUDA_VERSION_PATCH :=
# Found NVCC
else
  CUDA_VERSION_RAW := $(shell ${NVCC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)
  ifeq (${CUDA_VERSION_RAW},)
    $(error Not found CUDA Version in ${NVCC} --version)
  endif

  CUDA_VERSION_MAJOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$1}')
  CUDA_VERSION_MINOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$2}')
  CUDA_VERSION_PATCH := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$3}')

  HAVE_CUDA := 1
  export HAVE_CUDA
endif

ifneq ($(wildcard $(NCCL_H)),)
  HAVE_NCCL := 1
  export HAVE_NCCL
else
  $(warning Not found NVIDIA NCCL)
endif

export NVCC CUOBJDUMP NVDISASM CUDA_ROOT
export CUDA_VERSION_MAJOR CUDA_VERSION_MINOR CUDA_VERSION_PATCH

ifdef DEBUG
  $(info HAVE_CUDA = ${HAVE_CUDA})
  $(info HAVE_NCCL = ${HAVE_NCCL})
  ifneq (${NVCC},)
    $(info $(shell ${NVCC} --version))
  endif
  $(info NVCC = ${NVCC})
  $(info NVCC VERSION: $(shell ${NVCC} --version))
  $(info CUDA_VERSION_MAJOR = ${CUDA_VERSION_MAJOR})
  $(info CUDA_VERSION_MINOR = ${CUDA_VERSION_MINOR})
  $(info CUDA_VERSION_PATCH = ${CUDA_VERSION_PATCH})
endif

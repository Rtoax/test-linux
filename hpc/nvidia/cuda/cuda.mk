# SPDX-License-Identifier: GPL-3.0
_CUDA = 1

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
  ifneq ($(targets-nvcc),)
    $(error Not found nvcc, install cuda first)
  else
    $(warning Although not found nvcc, but you don't have targets-nvcc)
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
endif

export NVCC CUOBJDUMP NVDISASM CUDA_ROOT
export CUDA_VERSION_MAJOR CUDA_VERSION_MINOR CUDA_VERSION_PATCH

ifdef DEBUG
  ifneq (${NVCC},)
    $(info $(shell ${NVCC} --version))
  endif
  $(info NVCC = ${NVCC})
  $(info NVCC VERSION: $(shell ${NVCC} --version))
  $(info CUDA_VERSION_MAJOR = ${CUDA_VERSION_MAJOR})
  $(info CUDA_VERSION_MINOR = ${CUDA_VERSION_MINOR})
  $(info CUDA_VERSION_PATCH = ${CUDA_VERSION_PATCH})
endif

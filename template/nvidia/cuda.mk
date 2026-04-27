# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output macros:
# - HAVE_CUDA=[y|n]
# - HAVE_CUDNN=[y]
# - HAVE_CUFILE=[y]	GPUDirect Storage
# - HAVE_CUPTI=[y]	CUDA Profiling Tools Interface
# - HAVE_NVRTC=[y]      RTC: RunTime Compilation
#
# - CUDA_ROOT=[/usr/local/cuda/,/usr/]
#
# - NVCC=
# - CUOBJDUMP=
# - NVDISASM=
#
# - SYS_CUDA_VERSION=[13000]
# - CUDA_VERSION_MAJOR=[0]
# - CUDA_VERSION_MINOR=[0]
# - CUDA_VERSION_PATCH=[0]
#
# - cuda-cflags=-DHAVE_CUDA=1 ...
# - cuda-ldflags=...
#
# Functions:
# - cuda_{ge,gt,eq,lt,le}()=[y|n]
#
ifndef _NVIDIA_CUDA_MK
_NVIDIA_CUDA_MK = 1

include define.mk
include shell.mk
include version.mk

NVCC := $(shell which nvcc 2>/dev/null)
CUOBJDUMP := $(shell which cuobjdump 2>/dev/null)
NVDISASM := $(shell which nvdisasm 2>/dev/null)

SYS_CUDA_VERSION := 0
CUDA_VERSION_MAJOR := 0
CUDA_VERSION_MINOR := 0
CUDA_VERSION_PATCH := 0

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
    $(info Not found cuda toolkit, please install cuda-toolkit first!)
    CUDA_ROOT :=
  endif
endif

# Use env's nvcc first
ifeq ($(NVCC),)
  ifneq (${CUDA_ROOT},)
    NVCC := ${CUDA_ROOT}/bin/nvcc
    CUOBJDUMP := ${CUDA_ROOT}/bin/cuobjdump
    NVDISASM := ${CUDA_ROOT}/bin/nvdisasm
  endif
endif

ifneq ($(NVCC),)
  NVCC := $(shell realpath ${NVCC})
  CUOBJDUMP := $(shell realpath ${CUOBJDUMP})
  NVDISASM := $(shell realpath ${NVDISASM})

  # When use cu-bridge, NVCC is not empty, however, CUDA_ROOT is empty. Thus,
  # just set cuda root to cu-bridge.
  ifeq (${CUDA_ROOT},)
    CUDA_ROOT := $(shell realpath $(dir ${NVCC})/../)
  endif

  # When use cu-bridge and cuda-toolkit was installed. because NVCC is set to
  # cu-bridge, but CUDA_ROOT is real cuda path, we shoud reset CUDA_ROOT to
  # cu-bridge.
  ifneq ($(filter ${CUDA_ROOT},${NVCC}),${CUDA_ROOT})
    CUDA_ROOT := $(shell realpath $(dir ${NVCC})/../)
  endif
endif

# If not found NVCC
ifeq ($(wildcard $(NVCC)),)
  $(warning Not found nvcc, please install cuda-toolkit first!)

  NVCC :=
  CUOBJDUMP :=
  NVDISASM :=

  export HAVE_CUDA := n
# Found NVCC
else
  CUDA_VERSION_RAW := $(shell ${NVCC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)
  ifeq (${CUDA_VERSION_RAW},)
    $(error Not found CUDA Version in ${NVCC} --version)
  endif

  CUDA_VERSION_MAJOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$1}')
  CUDA_VERSION_MINOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$2}')
  CUDA_VERSION_PATCH := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$3}')

  export HAVE_CUDA := y
  cuda-cflags += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
  cuda-cflags += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
  cuda-cflags += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}
  cuda-cflags += -I${CUDA_ROOT}/include/
  cuda-cflags += -DHAVE_CUDA=1
endif

ifneq (${CUDA_ROOT},)
  SYS_CUDA_VERSION := $(shell grep '^#define CUDA_VERSION' ${CUDA_ROOT}/include/cuda.h | awk '{print $$3}')
  ifeq (${SYS_CUDA_VERSION},)
    SYS_CUDA_VERSION := 0
  endif
endif

$(eval $(call define_version,cuda,version2_code100010,${CUDA_VERSION_MAJOR},${CUDA_VERSION_MINOR}))

$(call check_file_and_def,${CUDA_ROOT}/include/cudnn.h,HAVE_CUDNN)
$(call check_file_and_def,${CUDA_ROOT}/include/cupti.h,HAVE_CUPTI)
$(call check_file_and_def,${CUDA_ROOT}/include/nvrtc.h,HAVE_NVRTC)
$(call check_file_and_def,${CUDA_ROOT}/include/cufile.h,HAVE_CUFILE)

$(if ${HAVE_CUDNN}, $(eval cuda-cflags += -DHAVE_CUDNN=1))
$(if ${HAVE_CUPTI}, $(eval cuda-cflags += -DHAVE_CUPTI=1))
$(if ${HAVE_CUFILE}, $(eval cuda-cflags += -DHAVE_CUFILE=1))
$(if ${HAVE_NVRTC}, $(eval cuda-cflags += -DHAVE_NVRTC=1))

$(if ${HAVE_CUDNN}, $(eval cuda-ldflags += -lcudnn))
$(if ${HAVE_CUPTI}, $(eval cuda-ldflags += -lcupti))
$(if ${HAVE_CUFILE}, $(eval cuda-ldflags += -lcufile))
$(if ${HAVE_NVRTC}, $(eval cuda-ldflags += -lnvrtc))

ifdef DEBUG
  $(info HAVE_CUDA = ${HAVE_CUDA})
  $(info HAVE_CUDNN = ${HAVE_CUDNN})
  $(info HAVE_CUPTI = ${HAVE_CUPTI})
  $(info HAVE_CUFILE = ${HAVE_CUFILE})
  $(info CUDA_ROOT = ${CUDA_ROOT})
  ifneq (${NVCC},)
    $(info NVCC Version $(shell ${NVCC} --version))
  endif
  $(info NVCC = ${NVCC})
  $(info SYS_CUDA_VERSION = ${SYS_CUDA_VERSION})
  $(info CUDA_VERSION_MAJOR = ${CUDA_VERSION_MAJOR})
  $(info CUDA_VERSION_MINOR = ${CUDA_VERSION_MINOR})
  $(info CUDA_VERSION_PATCH = ${CUDA_VERSION_PATCH})
  $(info cuda-cflags = ${cuda-cflags})
  $(info cuda-ldflags = ${cuda-ldflags})
endif

# When use cu-bridge, NVCC is cu-bridge symlink, cuda_VERSION_CODE is not zero.
ifneq (${SYS_CUDA_VERSION},0)
  ifneq (${SYS_CUDA_VERSION},${cuda_VERSION_CODE})
    $(error "SYS_CUDA_VERSION(${SYS_CUDA_VERSION}) != cuda_VERSION_CODE(${cuda_VERSION_CODE})")
  endif
endif

ifneq ($(call cuda_eq,${CUDA_VERSION_MAJOR},${CUDA_VERSION_MINOR}),y)
  $(error "Bad cuda_eq parse cuda_VERSION_CODE=${cuda_VERSION_CODE}")
endif
ifeq ($(call cuda_ge,14,0),y)
  $(error "Bad cuda_ge, does CUDA V14 released??????")
endif

export CUDA_ROOT
export NVCC
export CUOBJDUMP
export NVDISASM
export CUDA_VERSION_MAJOR
export CUDA_VERSION_MINOR
export CUDA_VERSION_PATCH
export cuda-cflags

endif

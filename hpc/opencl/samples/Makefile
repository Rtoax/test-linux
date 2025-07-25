# SPDX-License-Identifier: GPL-3.0
include ../../../compiler/compiler.mk
targets := clGetPlatformIDs

have_libopencl := $(findstring 1,$(call check_compiler_option,$(CC),-lOpenCL))
ifneq (${have_libopencl},1)
  $(error Found OpenCL)
endif

LDFLAGS := -lOpenCL

CFLAGS += -DCL_TARGET_OPENCL_VERSION=100

include ../../../template/main.mk

clGetPlatformIDs: clGetPlatformIDs.o

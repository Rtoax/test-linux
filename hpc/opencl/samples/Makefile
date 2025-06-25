# SPDX-License-Identifier: GPL-3.0
include ../../../compiler/compiler.mk
TARGETS :=
TARGETS_CL := clGetPlatformIDs

have_libopencl := $(findstring 1,$(call check_compiler_option,$(CC),-lOpenCL))
ifeq (${have_libopencl},1)
  $(info Found OpenCL)
  CFLAGS += -lOpenCL
  LDFLAGS += -lOpenCL
  TARGETS += $(TARGETS_CL)
endif

CFLAGS += -DCL_TARGET_OPENCL_VERSION=100

include ../../../template/main.mk

clGetPlatformIDs: clGetPlatformIDs.o

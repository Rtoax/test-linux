# SPDX-License-Identifier: GPL-3.0
include opencl.mk

target-${HAVE_OPENCL} := clGetPlatformIDs

LDFLAGS := -lOpenCL
CFLAGS += -DCL_TARGET_OPENCL_VERSION=100

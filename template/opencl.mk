# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_OPENCL=[y|n]
# - opencl-cflags=
# - opencl-ldflags=
#
ifndef _OPENCL_MK
_OPENCL_MK = 1

OPENCL_H := /usr/include/CL/cl.h
opencl-cflags :=
opencl-ldflags :=

ifneq ($(wildcard $(OPENCL_H)),)
  opencl-cflags += -DHAVE_OPENCL=1
  opencl-ldflags += -lpmem
  export HAVE_OPENCL := y
else
  $(warning "WARNING: You need to install opencl")
  export HAVE_OPENCL := n
endif

endif

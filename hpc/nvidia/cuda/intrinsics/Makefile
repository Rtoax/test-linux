# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk

targets-post :=

ifdef HAVE_CUDA
  targets-nvcc := half-nv

  targets-post += $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
  targets-post += $(patsubst %,${OUTPUT}%.ptx,$(targets-nvcc))
  targets-post += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))
endif

ifdef HAVE_HIP
  targets-hipcc := half-hip
endif

ifdef HAVE_HPCC
  targets-htcc := half-hpcc
endif

include ../../../../template/main.mk

ifdef HAVE_CUDA
half-nv: ${OUTPUT}half.cu.o
endif

ifdef HAVE_HIP
${OUTPUT}half.hip.o: half.cu
half-hip: ${OUTPUT}half.hip.o
endif

ifdef HAVE_HPCC
${OUTPUT}half.hpcc.o: half.cu
half-hpcc: ${OUTPUT}half.hpcc.o
endif

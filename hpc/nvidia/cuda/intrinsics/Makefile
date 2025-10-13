# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk

targets-post :=

ifdef HAVE_CUDA
  # WARNING: must have -nv suffix.
  targets-nvcc := half-nv
  targets-nvcc += bfloat16-nv

  targets-post += $(patsubst %-nv,${OUTPUT}%.E.cu,$(targets-nvcc))
  targets-post += $(patsubst %-nv,${OUTPUT}%.ptx,$(targets-nvcc))
  targets-post += $(patsubst %-nv,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))
endif

ifdef HAVE_HIP
  targets-hipcc := half-hip
  targets-hipcc += bfloat16-hip
endif

ifdef HAVE_HPCC
  targets-htcc := half-hpcc
  targets-htcc += bfloat16-hpcc
endif

include ../../../../template/main.mk

half-nv: ${OUTPUT}half.cu.o
bfloat16-nv: ${OUTPUT}bfloat16.cu.o

${OUTPUT}half.hip.o: half.cu
half-hip: ${OUTPUT}half.hip.o
${OUTPUT}bfloat16.hip.o: bfloat16.cu
bfloat16-hip: ${OUTPUT}bfloat16.hip.o

${OUTPUT}half.hpcc.o: half.cu
half-hpcc: ${OUTPUT}half.hpcc.o
${OUTPUT}bfloat16.hpcc.o: bfloat16.cu
bfloat16-hpcc: ${OUTPUT}bfloat16.hpcc.o

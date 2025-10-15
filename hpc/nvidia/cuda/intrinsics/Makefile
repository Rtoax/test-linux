# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk

common-objs := half
common-objs += bfloat16
common-objs += float
common-objs += double

targets-post :=

ifdef HAVE_CUDA
  # WARNING: must have -nv suffix.
  targets-nvcc := $(patsubst %,%-nv,$(common-objs))

  targets-post += $(patsubst %-nv,${OUTPUT}%.E.cu,$(targets-nvcc))
  targets-post += $(patsubst %-nv,${OUTPUT}%.ptx,$(targets-nvcc))
  targets-post += $(patsubst %-nv,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))
endif

ifdef HAVE_HIP
  targets-hipcc := $(patsubst %,%-hip,$(common-objs))
endif

ifdef HAVE_HPCC
  targets-htcc := $(patsubst %,%-hpcc,$(common-objs))
endif

include ../../../../template/main.mk

HDRS := print.h compiler.h

${OUTPUT}half.cu.o: ${HDRS}
${OUTPUT}bfloat16.cu.o: ${HDRS}
${OUTPUT}float.cu.o: ${HDRS}
${OUTPUT}double.cu.o: ${HDRS}

half-nv: ${OUTPUT}half.cu.o
bfloat16-nv: ${OUTPUT}bfloat16.cu.o
float-nv: ${OUTPUT}float.cu.o
double-nv: ${OUTPUT}double.cu.o

${OUTPUT}half.hip.o: half.cu ${HDRS}
half-hip: ${OUTPUT}half.hip.o
${OUTPUT}bfloat16.hip.o: bfloat16.cu ${HDRS}
bfloat16-hip: ${OUTPUT}bfloat16.hip.o
${OUTPUT}float.hip.o: float.cu ${HDRS}
float-hip: ${OUTPUT}float.hip.o
${OUTPUT}double.hip.o: double.cu ${HDRS}
double-hip: ${OUTPUT}double.hip.o

${OUTPUT}half.hpcc.o: half.cu ${HDRS}
half-hpcc: ${OUTPUT}half.hpcc.o
${OUTPUT}bfloat16.hpcc.o: bfloat16.cu ${HDRS}
bfloat16-hpcc: ${OUTPUT}bfloat16.hpcc.o
${OUTPUT}float.hpcc.o: float.cu ${HDRS}
float-hpcc: ${OUTPUT}float.hpcc.o
${OUTPUT}double.hpcc.o: double.cu ${HDRS}
double-hpcc: ${OUTPUT}double.hpcc.o

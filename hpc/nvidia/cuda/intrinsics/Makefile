# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk

common-objs := fp6
common-objs += fp8
common-objs += half
common-objs += bfloat16
common-objs += float
common-objs += double
common-objs += fp128

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

# Skip warnings
# warning: designated initializers are a C++20 extension [-Wc++20-designator]
# warning: brace elision for designated initializer is a C99 extension [-Wc99-designator]
CFLAGS_HIPCC_half := -Wno-c99-designator -Wno-c++20-designator

include ../../../../template/main.mk

HDRS := print.h compiler.h types.h

${OUTPUT}fp6.cu.o: ${HDRS}
${OUTPUT}fp8.cu.o: ${HDRS}
${OUTPUT}half.cu.o: ${HDRS}
${OUTPUT}bfloat16.cu.o: ${HDRS}
${OUTPUT}float.cu.o: ${HDRS}
${OUTPUT}double.cu.o: ${HDRS}
${OUTPUT}fp128.cu.o: ${HDRS}

fp6-nv: ${OUTPUT}fp6.cu.o
fp8-nv: ${OUTPUT}fp8.cu.o
half-nv: ${OUTPUT}half.cu.o
bfloat16-nv: ${OUTPUT}bfloat16.cu.o
float-nv: ${OUTPUT}float.cu.o
double-nv: ${OUTPUT}double.cu.o
fp128-nv: ${OUTPUT}fp128.cu.o

${OUTPUT}fp6.hip.o: fp6.cu ${HDRS}
fp6-hip: ${OUTPUT}fp6.hip.o
${OUTPUT}fp8.hip.o: fp8.cu ${HDRS}
fp8-hip: ${OUTPUT}fp8.hip.o
${OUTPUT}half.hip.o: half.cu ${HDRS}
half-hip: ${OUTPUT}half.hip.o
${OUTPUT}bfloat16.hip.o: bfloat16.cu ${HDRS}
bfloat16-hip: ${OUTPUT}bfloat16.hip.o
${OUTPUT}float.hip.o: float.cu ${HDRS}
float-hip: ${OUTPUT}float.hip.o
${OUTPUT}double.hip.o: double.cu ${HDRS}
double-hip: ${OUTPUT}double.hip.o
${OUTPUT}fp128.hip.o: fp128.cu ${HDRS}
fp128-hip: ${OUTPUT}fp128.hip.o

${OUTPUT}fp6.hpcc.o: fp6.cu ${HDRS}
fp6-hpcc: ${OUTPUT}fp6.hpcc.o
${OUTPUT}fp8.hpcc.o: fp8.cu ${HDRS}
fp8-hpcc: ${OUTPUT}fp8.hpcc.o
${OUTPUT}half.hpcc.o: half.cu ${HDRS}
half-hpcc: ${OUTPUT}half.hpcc.o
${OUTPUT}bfloat16.hpcc.o: bfloat16.cu ${HDRS}
bfloat16-hpcc: ${OUTPUT}bfloat16.hpcc.o
${OUTPUT}float.hpcc.o: float.cu ${HDRS}
float-hpcc: ${OUTPUT}float.hpcc.o
${OUTPUT}double.hpcc.o: double.cu ${HDRS}
double-hpcc: ${OUTPUT}double.hpcc.o
${OUTPUT}fp128.hpcc.o: fp128.cu ${HDRS}
fp128-hpcc: ${OUTPUT}fp128.hpcc.o

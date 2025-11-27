# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include cuda.mk
include rocm.mk
include luca.mk
include hpcc.mk
include compiler.mk

__USE_CUDA_HELPERS__ = ${HAVE_CUDA}
__USE_LUCA_HELPERS__ = ${HAVE_LUCA}

common-objs := fft

# NVIDIA CUDA
target-nvcc-${HAVE_CUDA} := ${common-objs}

# AMD ROCm
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs))

# MetaX HPCC
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(metax-htcc-y))

# CESTC LUCA
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))

include main.mk

HIP_HELPERS := ${OUTPUT}cuda_helpers.hip.o
HPCC_HELPERS := ${OUTPUT}cuda_helpers.hpcc.o

${HIP_HELPERS}: cuda_helpers.h
${HPCC_HELPERS}: cuda_helpers.h

# CUDA
fft: ${OUTPUT}fft.cu.o ${CUDA_HELPERS}

# ROCm HIP
fft-hip: ${OUTPUT}fft.hip.o ${HIP_HELPERS}

# MetaX HPCC
fft-hpcc: ${OUTPUT}fft.hpcc.o ${HPCC_HELPERS}

# CESTC LUCA
fft-luca: ${OUTPUT}fft.luca.o ${LUCA_HELPERS}

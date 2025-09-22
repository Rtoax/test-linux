OUTPUT := .output/

targets-hipcc := parallel
targets-hipcc += sparse
targets-hipcc += rand
targets-hipcc += module
targets-hipcc += matrix-fp32

obj-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

targets-post := $(patsubst %,${OUTPUT}%,$(obj-fatbin))

# FIXME: on my fedora 42 env:
# fatal error: 'bits/c++config.h' file not found
CFLAGS_HIPCC := -I/usr/include/c++/15/x86_64-redhat-linux/

CFLAGS_HIPCC_matrix-fp32 := -DTEST_FP32=1

include ../../../../template/main.mk

${OUTPUT}cuda_helpers.hip.o: cuda_helpers.h
${OUTPUT}%.o: cuda_adapter.h

parallel: ${OUTPUT}parallel.hip.o ${OUTPUT}cuda_helpers.hip.o
sparse: ${OUTPUT}sparse.hip.o ${OUTPUT}cuda_helpers.hip.o
rand: ${OUTPUT}rand.hip.o ${OUTPUT}cuda_helpers.hip.o
module: ${OUTPUT}module.hip.o ${OUTPUT}cuda_helpers.hip.o
matrix-fp32: ${OUTPUT}matrix-fp32.hip.o ${OUTPUT}cuda_helpers.hip.o

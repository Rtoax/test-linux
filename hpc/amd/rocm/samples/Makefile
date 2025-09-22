OUTPUT := .output/

targets-hipcc := parallel
targets-hipcc += hello
targets-hipcc += sparse
targets-hipcc += fft
targets-hipcc += rand
targets-hipcc += module
targets-hipcc += matrix-fp32
targets-hipcc += __GNUC__
targets-hipcc += dim3
targets-hipcc += hipEvent
targets-hipcc += hipMalloc
targets-hipcc += hipMallocManaged
targets-hipcc += hipGetDeviceProperties
targets-hipcc += hipGetDeviceCount
targets-hipcc += hipDeviceGetP2PAttribute

obj-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

targets-post := $(patsubst %,${OUTPUT}%,$(obj-fatbin))

# FIXME: on my fedora 42 env:
# fatal error: 'bits/c++config.h' file not found
CFLAGS_HIPCC := -I/usr/include/c++/15/x86_64-redhat-linux/

CFLAGS_HIPCC_matrix-fp32 := -DTEST_FP32=1

include ../../../../template/main.mk

${OUTPUT}cuda_helpers.hip.o: cuda_helpers.h
${OUTPUT}%.o: cuda_adapter.h

hello: ${OUTPUT}hello.hip.o ${OUTPUT}cuda_helpers.hip.o
__GNUC__: ${OUTPUT}__GNUC__.hip.o
parallel: ${OUTPUT}parallel.hip.o ${OUTPUT}cuda_helpers.hip.o
sparse: ${OUTPUT}sparse.hip.o ${OUTPUT}cuda_helpers.hip.o
fft: ${OUTPUT}fft.hip.o ${OUTPUT}cuda_helpers.hip.o
dim3: ${OUTPUT}dim3.hip.o ${OUTPUT}cuda_helpers.hip.o
rand: ${OUTPUT}rand.hip.o ${OUTPUT}cuda_helpers.hip.o
module: ${OUTPUT}module.hip.o ${OUTPUT}cuda_helpers.hip.o
matrix-fp32: ${OUTPUT}matrix-fp32.hip.o ${OUTPUT}cuda_helpers.hip.o
hipEvent: ${OUTPUT}hipEvent.hip.o ${OUTPUT}cuda_helpers.hip.o
hipMalloc: ${OUTPUT}hipMalloc.hip.o ${OUTPUT}cuda_helpers.hip.o
hipMallocManaged: ${OUTPUT}hipMallocManaged.hip.o ${OUTPUT}cuda_helpers.hip.o
hipGetDeviceProperties: ${OUTPUT}hipGetDeviceProperties.hip.o ${OUTPUT}cuda_helpers.hip.o
hipGetDeviceCount: ${OUTPUT}hipGetDeviceCount.hip.o ${OUTPUT}cuda_helpers.hip.o
hipDeviceGetP2PAttribute: ${OUTPUT}hipDeviceGetP2PAttribute.hip.o ${OUTPUT}cuda_helpers.hip.o

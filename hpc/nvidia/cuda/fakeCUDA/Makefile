# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

include ../cuda.mk

targets-libso := libcuda.so.1
targets-libso += libcudart.so.13
targets-libso += libcublas.so.13
targets-libso += libcublasLt.so.13
targets-libso += libcufft.so.12
targets-libso += libcurand.so.10
targets-libso += libcusparse.so.12

CFLAGS_SO := -I/usr/local/cuda/include/
CFLAGS_SO += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
CFLAGS_SO += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
CFLAGS_SO += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}
ifdef HAVE_CUDA
  $(info HAVE_CUDA)
  CFLAGS_SO += -DHAVE_CUDA=1
endif

LDFLAGS_SO_libcuda.so.1 := -Wl,--version-script=libcuda.map
LDFLAGS_SO_libcudart.so.13 := -Wl,--version-script=libcudart.map
LDFLAGS_SO_libcublas.so.13 := -Wl,--version-script=libcublas.map
LDFLAGS_SO_libcublasLt.so.13 := -Wl,--version-script=libcublasLt.map
LDFLAGS_SO_libcurand.so.10 := -Wl,--version-script=libcurand.map
LDFLAGS_SO_libcufft.so.12 := -Wl,--version-script=libcufft.map
LDFLAGS_SO_libcusparse.so.12 := -Wl,--version-script=libcusparse.map

include ../../../../template/main.mk

common-objs := ${OUTPUT}common.so.o
runtime-objs := ${OUTPUT}runtime.so.o
runtime-objs += ${OUTPUT}runtime_event.so.o
runtime-objs += ${OUTPUT}runtime_memory.so.o
runtime-objs += ${OUTPUT}runtime_internal.so.o
runtime-objs += ${OUTPUT}device.so.o

libcuda.so.1: ${common-objs} ${OUTPUT}cuda.so.o ${OUTPUT}cuda-module-mgmt.so.o ${OUTPUT}device.so.o
libcudart.so.13: ${common-objs} ${runtime-objs}
libcublas.so.13: ${common-objs} ${OUTPUT}blas.so.o
libcublasLt.so.13: ${common-objs} ${OUTPUT}blasLt.so.o
libcufft.so.12: ${common-objs} ${OUTPUT}fft.so.o
libcurand.so.10: ${common-objs} ${OUTPUT}rand.so.o
libcusparse.so.12: ${common-objs} ${OUTPUT}sparse.so.o

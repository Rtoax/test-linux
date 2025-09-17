# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

include ../cuda.mk
include ../../../metax/hpcc.mk

targets-libso-cpp := libcuda.so.1
targets-libso-cpp += libcudart.so.13
targets-libso-cpp += libcublas.so.13
targets-libso-cpp += libcublasLt.so.13
targets-libso-cpp += libcufft.so.12
targets-libso-cpp += libcurand.so.10
targets-libso-cpp += libcusparse.so.12

ifdef HAVE_HPCC
  $(info HAVE_HPCC)
  # need cuda_adapter.h
  CXXFLAGS_SO += -I../
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/common/
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/hcr/
  CXXFLAGS_SO += -DHAVE_HCCL=1
  CXXFLAGS_SO += -DHAVE_HPCC=1
else ifdef HAVE_CUDA
  $(info HAVE_CUDA)
  CXXFLAGS_SO := -I/usr/local/cuda/include/
  CXXFLAGS_SO += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
  CXXFLAGS_SO += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
  CXXFLAGS_SO += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}

  CXXFLAGS_SO += -DHAVE_CUDA=1
endif

LDXXFLAGS_SO_libcuda.so.1 := -Wl,--version-script=libcuda.map
LDXXFLAGS_SO_libcudart.so.13 := -Wl,--version-script=libcudart.map
LDXXFLAGS_SO_libcublas.so.13 := -Wl,--version-script=libcublas.map
LDXXFLAGS_SO_libcublasLt.so.13 := -Wl,--version-script=libcublasLt.map
LDXXFLAGS_SO_libcurand.so.10 := -Wl,--version-script=libcurand.map
LDXXFLAGS_SO_libcufft.so.12 := -Wl,--version-script=libcufft.map
LDXXFLAGS_SO_libcusparse.so.12 := -Wl,--version-script=libcusparse.map

include ../../../../template/main.mk

common-objs := ${OUTPUT}common.cpp.so.o
runtime-objs := ${OUTPUT}runtime.cpp.so.o
runtime-objs += ${OUTPUT}runtime_event.cpp.so.o
runtime-objs += ${OUTPUT}runtime_memory.cpp.so.o
runtime-objs += ${OUTPUT}runtime_internal.cpp.so.o
runtime-objs += ${OUTPUT}device.cpp.so.o

libcuda.so.1: ${common-objs} ${OUTPUT}cuda.cpp.so.o ${OUTPUT}cuda-module-mgmt.cpp.so.o ${OUTPUT}device.cpp.so.o
libcudart.so.13: ${common-objs} ${runtime-objs}
libcublas.so.13: ${common-objs} ${OUTPUT}blas.cpp.so.o
libcublasLt.so.13: ${common-objs} ${OUTPUT}blasLt.cpp.so.o
libcufft.so.12: ${common-objs} ${OUTPUT}fft.cpp.so.o
libcurand.so.10: ${common-objs} ${OUTPUT}rand.cpp.so.o
libcusparse.so.12: ${common-objs} ${OUTPUT}sparse.cpp.so.o

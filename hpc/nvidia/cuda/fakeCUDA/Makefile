# SPDX-License-Identifier: GPL-3.0

targets-libso := libcuda.so.1
targets-libso += libcudart.so.13
targets-libso += libcublas.so.13
targets-libso += libcublasLt.so.13
targets-libso += libcufft.so.12
targets-libso += libcurand.so.10
targets-libso += libcusparse.so.12

CFLAGS_SO := -I/usr/local/cuda/include/

LDFLAGS_SO_libcuda.so.1 := -Wl,--version-script=libcuda.map
LDFLAGS_SO_libcudart.so.13 := -Wl,--version-script=libcudart.map
LDFLAGS_SO_libcublas.so.12 := -Wl,--version-script=libcublas.map
LDFLAGS_SO_libcublasLt.so.12 := -Wl,--version-script=libcublasLt.map
LDFLAGS_SO_libcurand.so.10 := -Wl,--version-script=libcurand.map
LDFLAGS_SO_libcufft.so.12 := -Wl,--version-script=libcufft.map
LDFLAGS_SO_libcusparse.so.12 := -Wl,--version-script=libcusparse.map

include ../../../../template/main.mk

libcuda.so.1: cuda.so.o
libcudart.so.13: runtime.so.o internal.so.o
libcublas.so.13: blas.so.o
libcublasLt.so.13: blasLt.so.o
libcufft.so.12: fft.so.o
libcurand.so.10: rand.so.o
libcusparse.so.12: sparse.so.o

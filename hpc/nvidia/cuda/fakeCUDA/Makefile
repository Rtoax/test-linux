# SPDX-License-Identifier: GPL-3.0

targets-libso := libcuda.so.1.1
targets-libso += libcudart.so.13
targets-libso += libcublas.so.13.1
targets-libso += libcublasLt.so.13.1
targets-libso += libcufft.so.12.1
targets-libso += libcurand.so.10.1
targets-libso += libcusparse.so.12.1

CFLAGS_SO := -I/usr/local/cuda/include/

LDFLAGS_SO_libcudart.so.13 := -Wl,--version-script=libcudart.map

include ../../../../template/main.mk

libcuda.so.1.1: cuda.so.o
libcudart.so.13: runtime.so.o internal.so.o
libcublas.so.13.1: blas.so.o
libcublasLt.so.13.1: blasLt.so.o
libcufft.so.12.1: fft.so.o
libcurand.so.10.1: rand.so.o
libcusparse.so.12.1: sparse.so.o

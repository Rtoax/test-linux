# SPDX-License-Identifier: GPL-3.0

targets-libso := libcuda.so.1.1
targets-libso += libcudart.so.13.1

CFLAGS_SO := -I/usr/local/cuda/include/

include ../../../../template/main.mk

libcuda.so.1.1: cuda.so.o
libcudart.so.13.1: runtime.so.o internal.so.o

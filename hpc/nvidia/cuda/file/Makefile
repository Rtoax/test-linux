# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk

common-objs := hello

target-cpp-${HAVE_CUFILE} := ${common-objs}

CXXFLAGS += -I${CUDA_ROOT}/include/
LDXXFLAGS += -L${CUDA_ROOT}/lib64/
LDXXFLAGS += -lcuda -lcufile -lcudart

include main.mk

hello: ${OUTPUT}hello.cpp.o

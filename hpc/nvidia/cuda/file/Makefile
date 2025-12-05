# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include cuda.mk

common-objs := hello

target-nvcc-${HAVE_CUFILE} := ${common-objs}

include main.mk

hello: ${OUTPUT}hello.cu.o

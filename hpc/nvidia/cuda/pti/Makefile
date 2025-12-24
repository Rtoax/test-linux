# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
OUTPUT := .output/

include cuda.mk

target-nvcc-y := subscribe

CFLAGS_NVCC := -I../

include main.mk

subscribe: ${OUTPUT}subscribe.cu.o

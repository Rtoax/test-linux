# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ../../../../compiler/compiler.mk

targets-nvcc := half

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.ptx,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))

include ../../../../template/main.mk

half: ${OUTPUT}half.cu.o

# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include ../cuda.mk
include ../../../metax/hpcc.mk

targets-post :=

ifdef HAVE_CUDA
  targets-nvcc := half

  targets-post += $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
  targets-post += $(patsubst %,${OUTPUT}%.ptx,$(targets-nvcc))
  targets-post += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))

else ifdef HAVE_HPCC
  targets-htcc := half
endif

include ../../../../template/main.mk

ifdef HAVE_CUDA
half: ${OUTPUT}half.cu.o
else ifdef HAVE_HPCC
half: ${OUTPUT}half.hpcc.o
endif

# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
#
# Output definitions:
#
_GCC_MK = 1

GCC := gcc
GXX := g++

CC = ${GCC}
CXX = ${GXX}

include compiler.mk

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
endif

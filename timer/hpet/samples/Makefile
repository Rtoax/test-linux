SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


# SPDX-License-Identifier: GPL-2.0
all:
	gcc hpet_example.c 

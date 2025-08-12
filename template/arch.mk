# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

ifeq ($(shell uname -m),sw_64)
  ifeq ($(shell lscpu | grep -o WX-H8000 || true),WX-H8000)
    CFLAGS += -mcpu=sw8a
  else ifeq ($(shell lscpu | grep -o SW3231 || true),SW3231)
    CFLAGS += -mcpu=sw6b
  endif
endif


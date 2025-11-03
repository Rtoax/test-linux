# SPDX-License-Identifier: GPL-3.0

ifeq ($(shell uname -m),x86_64)
  $(info x86_64)
else ifeq ($(shell uname -m),aarch64)
  $(info aarch64)
endif

ifeq (1 2 3,1 2 3)
  $(info 1 2 3 == 1 2 3)
endif

.PHONY: build
build:


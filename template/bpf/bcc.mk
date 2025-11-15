# SPDX-License-Identifier: GPL-3.0
_BCC = 1

LIBBCC_PATH := $(shell ldconfig -p | grep libbcc.so | awk '{print $$NF}' | head -1)
LIBBCC_PATH := $(shell realpath ${LIBBCC_PATH})

ifdef DEBUG
  $(info LIBBCC_PATH = ${LIBBCC_PATH})
endif

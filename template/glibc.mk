# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - GLIBC_VERSION=
# - LIBC_SO_PATH=
#
# Functions:
# - probe_libc_printf()
# - libc_sym_addr()
#
_GLIBC_MK = 1

GLIBC_VERSION := $(shell getconf GNU_LIBC_VERSION)

# Get libc.so.6 abs-path
LIBC_SO_PATH := $(shell ldconfig -p | grep libc.so.6 | awk '{printf $$NF"\n"}' | head -1)

# Probe printf(3) with non-output gcc command
LIBC_PRINTF_PROBE := '\#include <stdio.h>\n'
LIBC_PRINTF_PROBE += 'int main(void) {\n'
LIBC_PRINTF_PROBE += '	printf("hello\\n");\n'
LIBC_PRINTF_PROBE += '}'

define probe_libc_printf
  $(shell printf '%b\n' $(LIBC_PRINTF_PROBE) | \
    $(CC) -x c -Wall - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

# Get symbol address from libc.so.6, readelf output format
#
# 2611: 0000000000035a80   204 FUNC    GLOBAL DEFAULT    3 printf@@GLIBC_2.2.5
#
# $1 - symbol
define libc_sym_addr
$(shell readelf --syms --wide ${LIBC_SO_PATH} \
		| grep -w $(1) | grep -e GLOBAL -e LOCAL | head -1 \
		| awk '{printf "0x"$$2}')
endef

ifdef DEBUG
  $(info GLIBC_VERSION = ${GLIBC_VERSION})
  $(info LIBC_SO_PATH = ${LIBC_SO_PATH})
  $(info printf = <$(call libc_sym_addr,printf)>)
endif

export GLIBC_VERSION LIBC_SO_PATH

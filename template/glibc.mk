# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LIBC_SO_PATH=
#
# Functions:
# - probe_libc_printf()
# - libc_sym_addr()
#
_GLIBC = 1

GLIBC_VERSION := $(shell getconf GNU_LIBC_VERSION)

# Get libc.so.6 abs-path
LIBC_SO_PATH := $(shell ldconfig -p | grep libc.so.6 | awk '{printf $$NF"\n"}' | head -1)

LIBC___ERRNO_LOCATION_SYMADDR := 0x$(shell readelf --syms --wide ${LIBC_SO_PATH} \
				| grep -w __errno_location | head -1 \
				| awk '{printf $$2}')

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
  $(info LIBC___ERRNO_LOCATION_SYMADDR = ${LIBC___ERRNO_LOCATION_SYMADDR})
  $(info printf = <$(call libc_sym_addr,printf)>)
endif

export LIBC_SO_PATH

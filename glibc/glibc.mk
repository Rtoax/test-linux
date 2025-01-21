# SPDX-License-Identifier: GPL-3.0

pound := \#

LIBC_SO_PATH=$(shell ldconfig -p | grep libc.so.6 | grep 64 | awk '{printf $$NF}')
$(info LIBC_SO_PATH = ${LIBC_SO_PATH})

LIBC_PRINTF_SYMADDR=0x$(shell readelf --syms --wide ${LIBC_SO_PATH} \
				| grep -w printf | head -1 \
				| awk '{printf $$2}')
$(info LIBC_PRINTF_SYMADDR = ${LIBC_PRINTF_SYMADDR})

LIBC___ERRNO_LOCATION_SYMADDR=0x$(shell readelf --syms --wide ${LIBC_SO_PATH} \
				| grep -w __errno_location | head -1 \
				| awk '{printf $$2}')
$(info LIBC___ERRNO_LOCATION_SYMADDR = ${LIBC___ERRNO_LOCATION_SYMADDR})


# Probe printf(3) with non-output gcc command
PRINTF_PROBE := '$(pound)include <stdio.h>\n'
PRINTF_PROBE += 'int main(void) {\n'
PRINTF_PROBE += '	printf("hello\\n");\n'
PRINTF_PROBE += '}'
define probe_libc_printf
  $(shell printf '%b\n' $(PRINTF_PROBE) | \
    $(CC) -x c -Wall - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

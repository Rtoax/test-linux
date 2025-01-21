# SPDX-License-Identifier: GPL-3.0

LIBC_SO_PATH=$(shell ldconfig -p | grep libc.so.6 | grep 64 | awk '{printf $$4}')
$(info LIBC_SO_PATH = ${LIBC_SO_PATH})

LIBC___ERRNO_LOCATION_SYMADDR=0x$(shell readelf --syms --wide ${LIBC_SO_PATH} \
				| grep -w __errno_location \
				| awk '{printf $$2}')
$(info LIBC___ERRNO_LOCATION_SYMADDR = ${LIBC___ERRNO_LOCATION_SYMADDR})


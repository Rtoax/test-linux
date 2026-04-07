// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

const static union __attribute__((unused)) {
	char c[4];
	unsigned long mylong;
} endian_test = {{'l', '?', '?', 'b'}};

#define ENDIANNESS ((char)endian_test.mylong)
#define is_little_endian() (ENDIANNESS == 'l')
#define is_big_endian() (ENDIANNESS == 'b')

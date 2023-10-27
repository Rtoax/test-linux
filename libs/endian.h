#pragma once

const static union __attribute__((unused)) {
	char c[4];
	unsigned long mylong;
} endian_test = {{'l', '?', '?', 'b'}};

#define ENDIANNESS ((char)endian_test.mylong)
#define is_little_endian() (ENDIANNESS == 'l')
#define is_big_endian() (ENDIANNESS == 'b')

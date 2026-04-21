// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdint.h>
#include "byte.h"

#ifdef TEST_MAIN
int main(void)
{
	uint64_t u64 = 0xffff000012345678UL;
	uint32_t u32 = 0x12345678UL;
	uint16_t u16 = 0x5678UL;

	printf("%lx -> %lx\n", u64, byteswap64(u64));
	printf("%x -> %x\n", u32, byteswap32(u32));
	printf("%x -> %x\n", u16, byteswap16(u16));
	return 0;
}
#endif

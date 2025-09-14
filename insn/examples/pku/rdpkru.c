#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdint.h>
#include <sys/mman.h>

static uint32_t pkru;

static inline void read__rdpkru_u32(void)
{
	asm volatile(
		"xor %%ecx, %%ecx \n"
		"movl $0, %%ecx; rdpkru \n"
		: "=a"(pkru)
		:
		: "ecx");
}

int main(void)
{
	int pkey = pkey_alloc(0, 0);
	(void)pkey;
	read__rdpkru_u32();
	return 0;
}

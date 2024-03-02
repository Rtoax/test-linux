/**
 * File: _mm_clflush.c
 * Author: Rong Tao <rtoax@foxmail.com>
 * Date: 2022.05.06
 *
 * _mm_clflush() will flush cacheline if vars in cache.
 *
 * Refs:
 * https://www.codenong.com/52525886/
 * https://zhuanlan.zhihu.com/p/242740319
 */
#include <stdio.h>
#include <stdint.h>

#if defined(__x86_64__)
#include <mmintrin.h>
#include <x86intrin.h>
#else
# error "Not support"
#endif

#ifndef FLUSH
# warning "Define FLUSH test _mm_clflush."
#endif

#define LINE_SIZE   64

#define L1_WAYS     16
#define L1_SETS     64
#define L1_LINES    512

extern void _mm_clflush(void const*_P);

uint8_t data[L1_LINES*LINE_SIZE];

int main(int argc, char *argv[])
{
	volatile uint8_t *addr;
	register uint64_t i;
	unsigned int junk = 0;
	register uint64_t t1, t2;

	printf("data: %p\n", data);

	_mm_clflush(data);

	printf("accessing 16 bytes in a cache line:\n");

	for (i = 0; i < 16; i++) {
		t1 = __rdtscp(&junk);
		addr = &data[i];
		junk = *addr;
		t2 = __rdtscp(&junk) - t1;
#ifdef FLUSH
		/* Flush */
		_mm_clflush(data);
#endif
		printf("i = %2ld, cycles: %ld\n", i, t2);
	}

	return 0;
}


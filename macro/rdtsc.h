#pragma once

#ifndef RDTSC
#define RDTSC() ({\
	register uint32_t a,d; \
	__asm__ __volatile__( "rdtsc" : "=a"(a), "=d"(d)); \
	(((uint64_t)a)+(((uint64_t)d)<<32)); \
	})
#endif

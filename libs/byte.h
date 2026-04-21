#pragma once
#include <stdint.h>

/* see /usr/include/linux/swab.h */
#define ___constant_swab16(x) ((uint16_t)(				\
	(((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |			\
	(((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define ___constant_swab32(x) ((uint32_t)(				\
	(((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |		\
	(((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |		\
	(((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |		\
	(((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define ___constant_swab64(x) ((uint64_t)(				\
	(((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) |	\
	(((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) |	\
	(((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) |	\
	(((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) |	\
	(((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) |	\
	(((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) |	\
	(((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) |	\
	(((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

#define ___constant_swahw32(x) ((uint32_t)(			\
	(((uint32_t)(x) & (uint32_t)0x0000ffffUL) << 16) |		\
	(((uint32_t)(x) & (uint32_t)0xffff0000UL) >> 16)))

#define ___constant_swahb32(x) ((uint32_t)(			\
	(((uint32_t)(x) & (uint32_t)0x00ff00ffUL) << 8) |		\
	(((uint32_t)(x) & (uint32_t)0xff00ff00UL) >> 8)))

#ifndef byteswap64
#define byteswap64(x) ___constant_swab64(x)
#endif
#ifndef byteswap32
#define byteswap32(x) ___constant_swab32(x)
#endif
#ifndef byteswap16
#define byteswap16(x) ___constant_swab16(x)
#endif

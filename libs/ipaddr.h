// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <string.h>
#include <stdint.h>

#define __C2I(c) (c-'0')
#define __SLEN(s) strlen(s)
#define __POW10(i) ({				\
		int __i, __pow = 1;		\
		for (__i = 0; __i < i; __i++)	\
			__pow *= 10;		\
		__pow;				\
	})

#define __S2I(s) ({						\
		int __i = 0, __len = __SLEN(s), __I = 0;	\
		for (__i = 0; __i < __len; __i++) {		\
			int __ind = __len - 1 - __i;		\
			int __mag = __POW10(__ind);		\
			int __v = __C2I(s[__i]) * __mag;	\
			__I += __v;				\
		}						\
		__I;						\
	})

#define IPv4S(sa,sb,sc,sd)  IPv4(__S2I(sa), __S2I(sb), __S2I(sc), __S2I(sd))
#define IPv4(a, b, c, d) ((uint32_t)(((a) & 0xff) << 24) |	\
			(((b) & 0xff) << 16) |			\
			(((c) & 0xff) << 8) |			\
			((d) & 0xff))


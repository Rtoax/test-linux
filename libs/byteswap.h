#pragma once

#ifndef byteswap64
#define byteswap64(l64) \
			(((l64 >> 56) & 0xff)       | ((l64 & 0xff) << 56) |\
			 ((l64 >> 40) & 0xff00)     | ((l64 & 0xff00) << 40) |\
			 ((l64 >> 24) & 0xff0000)   | ((l64 & 0xff0000) << 24) |\
			 ((l64 >>  8) & 0xff000000) | ((l64 & 0xff000000) << 8))
#endif


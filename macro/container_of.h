#pragma once

#include "offsetof.h"

#ifndef container_of
#define container_of(ptr, type, member) ({	\
	const typeof(((type *)0)->member) *__mptr = (typeof(((type *)0)->member)*)(ptr);	\
	(type *)((char *)__mptr - offsetof(type, member));	\
	})
#endif

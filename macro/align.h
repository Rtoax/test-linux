#pragma once

#ifndef __packed
#define __packed __attribute__((packed))
#endif
#if 0
/* or */
#pragma pack(1)
struct A {
	int a;
	char b;
	double c;
};
#endif

#ifndef __aligned
#define __aligned(v)	__attribute__((aligned(v)))
#endif



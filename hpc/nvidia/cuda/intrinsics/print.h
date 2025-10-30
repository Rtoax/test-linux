/* This header must used to CUDA like compiler. */
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>


#define SEP	"│" /* good looking */

/* Print definitions */
#define PPFX()	printf("L%-4d" SEP " ", __LINE__);
#define PEXPR(expr)	PPFX();printf("%s\n", #expr); expr;

#define PFP8E8M0(v) do {	\
		__nv_bfloat16_raw ___bf16raw = __nv_cvt_e8m0_to_bf16raw(v);	\
		PPFX();	\
		printf("E8M0: %s : %f\n", #v, __bfloat162float(___bf16raw));	\
	} while (0)

#define PFP8x2E8M0(v) do {	\
		__nv_bfloat162_raw ___bf162raw = __nv_cvt_e8m0x2_to_bf162raw(v);	\
		PPFX();	\
		printf("E8M0: %s : {%f, %f}\n", #v, \
			__bfloat162float(___bf162raw.x), __bfloat162float(___bf162raw.y));	\
	} while (0)

#define PFP8E4M3(v) do {	\
		__half_raw ___hraw = __nv_cvt_fp8_to_halfraw(v, __NV_E4M3);	\
		PPFX();	\
		printf("E4M3: %s : %f\n", #v, __half2float(___hraw));	\
	} while (0)

#define PFP8x2E4M3(v) do {	\
		__half2_raw ___h2raw = __nv_cvt_fp8x2_to_halfraw2(v, __NV_E4M3);	\
		PPFX();	\
		printf("E4M3: %s : {%f, %f}\n", #v, __half2float(___h2raw.x), __half2float(___h2raw.y));	\
	} while (0)

#define PHALF(v)	PPFX();printf("%s : %f\n", #v, __half2float(v));
#define PHALFRAW(v)	PHALF(v)
#define PHALF2(v) do {	\
		half2 __h2 = v;	\
		PPFX();	\
		printf("%s : {%f, %f}\n", #v, __half2float(__h2.x), __half2float(__h2.y));	\
	} while (0)
#define PHALF2RAW(v)	PHALF2(v)

#define PFLOAT(v)	PPFX();printf("%s : %f\n", #v, v);
#define PFLOAT2(v) do {	\
		float2 __f2 = v;	\
		PPFX();	\
		printf("%s : {%f, %f}\n", #v, __f2.x, __f2.y);	\
	} while (0)

#define PBF16(v)	PPFX();printf("%s : %f\n", #v, __bfloat162float(v));
#define PBF16RAW(v)	PBF16(v)
#define __PBF162(type, v) do {	\
		type __bf162 = v;	\
		PPFX();	\
		printf("%s : {%f, %f}\n", #v, __bfloat162float(__bf162.x), __bfloat162float(__bf162.y));	\
	} while (0)
#define PBF162(v)	__PBF162(__nv_bfloat162, v)
#define PBF162RAW(v)	__PBF162(__nv_bfloat162_raw, v)

#define PDOUBLE(v)	PPFX();printf("%s : %lf\n", #v, v);
#define PDOUBLE2(v)	PPFX();printf("%s : {%lf, %lf}\n", #v, v.x, v.y);
#define PUINT32(v)	PPFX();printf("%s : %d\n", #v, v);
#define PUINT32toINT16x2(v) do {	\
		PPFX();	\
		short __s1 = v >> 16 & 0xffff;	\
		short __s2 = v & 0xffff;	\
		printf("%s : {%d, %d}\n", #v, __s1, __s2);	\
	} while (0)
#define PUINT32toINT8x4(v) do {	\
		PPFX();	\
		int8_t u1 = v >> 24 & 0xff;	\
		int8_t u2 = v >> 16 & 0xff;	\
		int8_t u3 = v >> 8 & 0xff;	\
		int8_t u4 = v & 0xff;	\
		printf("%s : {%d, %d, %d, %d}\n", #v, u1, u2, u3, u4);	\
	} while (0)
#define PUINT32toUINT8x4(v) do {	\
		PPFX();	\
		uint8_t u1 = v >> 24 & 0xff;	\
		uint8_t u2 = v >> 16 & 0xff;	\
		uint8_t u3 = v >> 8 & 0xff;	\
		uint8_t u4 = v & 0xff;	\
		printf("%s : {%u, %u, %u, %u}\n", #v, u1, u2, u3, u4);	\
	} while (0)
#define PUINT32toSHORT2(v) do {	\
		unsigned int __v = v;	\
		short2 s2 = *reinterpret_cast<short2 *>(&__v);	\
		PPFX();printf("%s : {%d, %d}\n", #v, s2.x, s2.y);	\
	} while (0)

#define PSHORT(v)	PPFX();printf("%s : %d\n", #v, v);
#define PSHORT2(v)	PPFX();printf("%s : {%d, %d}\n", #v, v.x, v.y);
#define PLONG(v)	PPFX();printf("%s : %ld\n", #v, v);
#define PLONGLONG(v)	PPFX();printf("%s : %lld\n", #v, v);
#define PBOOL(v)	PPFX();printf("%s : %s\n", #v, v ? "true" : "false");
#define PCHAR(v)	PPFX();printf("%s : %u (%c)\n", #v, v, v);

#define PBITS(mem, nbits) do {	\
		PPFX();		\
		printf("%s[1~%ld] : ", #mem, (size_t)nbits);	\
		for (size_t i = 0; i < nbits; i++) {	\
			uint8_t u8 = *(uint8_t *)((const int8_t *)mem + i / 8);	\
			uint8_t bit = (u8 >> (i % 8) & 0x1);	\
			printf("%c", bit ? '1' : '0');	\
		}	\
		printf("\n");	\
	} while (0)

static void fpbits(FILE *fp, const void *mem, size_t bits)
{
	size_t i;
	for (i = 0; i < bits; i++) {
		uint8_t u8 = *(uint8_t *)((const int8_t *)mem + i / 8);
		uint8_t bit = (u8 >> (i % 8) & 0x1);
		fprintf(fp, "%c", bit ? '1' : '0');
	}
}

static void pbits(const void *mem, size_t bits)
{
	fpbits(stdout, mem, bits);
}

/* This header must used to CUDA like compiler. */
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>


#define SEP	"│" /* good looking */

/* Print definitions */
#define PPFX()	printf("L%-4d" SEP " ", __LINE__);
#define PEXPR(expr)	PPFX();printf("%s\n", #expr); expr;

#define PFP8(v, interpretation) do {	\
		__half_raw ___hraw = __nv_cvt_fp8_to_halfraw(v, interpretation);	\
		PPFX();	\
		printf("%s <%s> : %f\n", #v, #interpretation, __half2float(___hraw));	\
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
#define __PBF162(type, v) do {	\
		type __bf162 = v;	\
		PPFX();	\
		printf("%s : {%f, %f}\n", #v, __bfloat162float(__bf162.x), __bfloat162float(__bf162.y));	\
	} while (0)
#define PBF162(v)	__PBF162(__nv_bfloat162, v)
#define PBF162RAW(v)	__PBF162(__nv_bfloat162_raw, v)

#define PDOUBLE(v)	PPFX();printf("%s : %lf\n", #v, v);
#define PINT(v)		PPFX();printf("%s : %d\n", #v, v);
#define PSHORT(v)	PPFX();printf("%s : %d\n", #v, v);
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

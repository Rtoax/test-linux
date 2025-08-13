#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "call.h"

extern const unsigned long _GLOBAL_OFFSET_TABLE_[];

#define GOT(idx) fn0_t *got##idx(void) { return (fn0_t *)_GLOBAL_OFFSET_TABLE_[idx]; }

GOT(3);
GOT(4);
GOT(5);
GOT(6);
GOT(7);
GOT(8);
GOT(9);
GOT(10);
GOT(11);
GOT(12);
GOT(13);
GOT(14);
GOT(15);
GOT(16);
GOT(17);
GOT(18);
GOT(19);
GOT(20);
GOT(21);
GOT(22);

fn0_t *gotidx(int idx)
{
	return (fn0_t *)_GLOBAL_OFFSET_TABLE_[idx];
}

#if defined(DIRECT_USE_GOT)

/**
 * This function is only needed on aarch64, because the GOT on x86_64 is
 * sequential. In order to eliminate the GOT entries of the string class,
 * this function is only implemented on aarch64.
 */
# if defined(__aarch64__)
int get_call_got_idx(int argc, char *argv[], int idx[])
{
	int i;
	for (i = 0; i < argc; i++) {
		if (!strncmp("GOT_IDX_CALL0", argv[i], 13)) {
			/**
			 * GOT_IDX_CALL06=27
			 *              ^^^^
			 */
			char *s = argv[i] + 13;
			int a = atoi(s);
			char *s2 = strstr(s, "=") + 1;
			idx[a - 1] = atoi(s2);
			fprintf(stderr, "idx[%d] = %d\n", a - 1, idx[a - 1]);
		}
	}
	return 0;
}
# endif
#endif

int main(int argc, char *argv[])
{
	uint64_t i, j;
	fn0_t *fns[20];

	/* Make sure dynamic linker/loader finish resolve GOT */
	call01();
	call02();
	call03();
	call04();
	call05();
	call06();
	call07();
	call08();
	call09();
	call010();
	call011();
	call012();
	call013();
	call014();
	call015();
	call016();
	call017();
	call018();
	call019();
	call020();

#if defined(DIRECT_USE_GOT)

	/**
	 * Using GOT directly can ensure the spatial continuity of memory.
	 * GOT[] is one of callxx(), x86_64 start from index 3, and aarch64
	 * start from 7.
	 */
# if defined(__x86_64__)
	fns[0] = got3();
	fns[1] = got4();
	fns[2] = got5();
	fns[3] = got6();
	fns[4] = got7();
	fns[5] = got8();
	fns[6] = got9();
	fns[7] = got10();
	fns[8] = got11();
	fns[9] = got12();
	fns[10] = got13();
	fns[11] = got14();
	fns[12] = got15();
	fns[13] = got16();
	fns[14] = got17();
	fns[15] = got18();
	fns[16] = got19();
	fns[17] = got20();
	fns[18] = got21();
	fns[19] = got22();
# elif defined(__aarch64__)
	int idx[20];
	get_call_got_idx(argc, argv, idx);

	for (i = 0; i < 20; i++)
		fns[i] = gotidx(idx[i]);
# endif
#else /* DIRECT_USE_GOT */
	/**
	 * call01 maybe is not got[3]
	 */
	fns[0] = call01;
	fns[1] = call02;
	fns[2] = call03;
	fns[3] = call04;
	fns[4] = call05;
	fns[5] = call06;
	fns[6] = call07;
	fns[7] = call08;
	fns[8] = call09;
	fns[9] = call010;
	fns[10] = call011;
	fns[11] = call012;
	fns[12] = call013;
	fns[13] = call014;
	fns[14] = call015;
	fns[15] = call016;
	fns[16] = call017;
	fns[17] = call018;
	fns[18] = call019;
	fns[19] = call020;
#endif /* DIRECT_USE_GOT */

#define NLOOP	1000000000UL

	for (i = 0; i < NLOOP; i++)
#if defined(ONLY_TEST_ONE_LLC_LINESIZE)
		/**
		 * Generally, LLC LINESIZE is 64 bytes, corresponding to 8
		 * items in GOT, and 5 callback functions can be called.
		 */
		#pragma GCC unroll 5
		for (j = 0; j < 5; j++)
#else
		#pragma GCC unroll 20
		for (j = 0; j < 20; j++)
#endif
			fns[j]();

	return 0;
}

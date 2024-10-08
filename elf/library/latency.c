#include <stdio.h>
#include <stdint.h>

#include "call.h"

#if defined(DIRECT_USE_GOT)
extern const unsigned long _GLOBAL_OFFSET_TABLE_[];

#define GOT(idx) fn0_t *got##idx(void) { return (fn0_t *)_GLOBAL_OFFSET_TABLE_[idx]; }

/* GOT[3] is one of call, start from index 3 */
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
#endif

int main(void)
{
	uint64_t i;
	uint64_t n = 1000000000UL;

#if defined(DIRECT_USE_GOT)
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

	fn0_t *fns[20];

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
#endif

	for (i = 0; i < n; i++) {
#if defined(DIRECT_USE_GOT)
		fns[0]();
		fns[1]();
		fns[2]();
		fns[3]();
		fns[4]();
		fns[5]();
		fns[6]();
		fns[7]();
		fns[8]();
		fns[9]();
		fns[10]();
		fns[11]();
		fns[12]();
		fns[13]();
		fns[14]();
		fns[15]();
		fns[16]();
		fns[17]();
		fns[18]();
		fns[19]();
#else
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
#endif
	}

	return 0;
}

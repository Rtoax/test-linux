#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "call.h"

DEFINE_CALL0(call01);
DEFINE_CALL0(call02);
DEFINE_CALL0(call03);
DEFINE_CALL0(call04);
DEFINE_CALL0(call05);
DEFINE_CALL0(call06);
DEFINE_CALL0(call07);
DEFINE_CALL0(call08);
DEFINE_CALL0(call09);
DEFINE_CALL0(call010);
DEFINE_CALL0(call011);
DEFINE_CALL0(call012);
DEFINE_CALL0(call013);
DEFINE_CALL0(call014);
DEFINE_CALL0(call015);
DEFINE_CALL0(call016);
DEFINE_CALL0(call017);
DEFINE_CALL0(call018);
DEFINE_CALL0(call019);
DEFINE_CALL0(call020);

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
}

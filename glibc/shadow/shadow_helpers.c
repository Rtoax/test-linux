// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include "shadow_helpers.h"

void display_spwd(struct spwd *spwd)
{
#define LS(v)	printf("%32s = %s\n", #v, spwd->v)
#define LI(v)	printf("%32s = %ld\n", #v, spwd->v)
	LS(sp_namp);
	LS(sp_pwdp);
	LI(sp_lstchg);
	LI(sp_min);
	LI(sp_max);
	LI(sp_warn);
	LI(sp_inact);
	LI(sp_expire);
	LI(sp_flag);
#undef LS
#undef LI
}

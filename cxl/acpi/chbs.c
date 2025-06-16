#include <stdio.h>
#include "chbs.h"

void display_chbs(struct chbs *chbs)
{
	printf("CHBS type %2d, len %4d, uid %4x, CXL version %2x, base %lx len %lx\n",
		chbs->type, chbs->record_length, chbs->uid,
		chbs->cxl_version, chbs->base, chbs->length);
}

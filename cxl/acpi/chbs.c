#include <stdio.h>
#include "chbs.h"

void display_chbs(struct chbs *chbs)
{
	printf("CHBS type %d, len %d, uid %x, CXL version %x, base %lx len %lx\n",
		chbs->type, chbs->record_length, chbs->uid,
		chbs->cxl_version, chbs->base, chbs->length);
}

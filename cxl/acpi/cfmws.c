#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "cfmws.h"

void display_cfmws(struct cfmws *cfmws)
{
	printf("CFMWS type %d, len %d, hpa %x, winsize %d, ENIW %d",
		cfmws->type, cfmws->record_length, cfmws->base_hpa,
		cfmws->window_size, cfmws->eniw);
	printf(", hbig %x, qtag id %d", cfmws->hbig, cfmws->qtag_id);
	/* TODO: display more */
	printf(", ...\n");
}

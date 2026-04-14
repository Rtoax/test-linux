#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "cfmws.h"
#include "constants.h"

void display_cfmws(struct cfmws *cfmws)
{
	printf("CFMWS type %d, len %d(0x%x), hpa %x, winsize %d, ENIW %d",
	       cfmws->type, cfmws->record_length, cfmws->record_length,
	       cfmws->base_hpa, cfmws->window_size, cfmws->eniw);
	printf(", hbig %x (%d MB)", cfmws->hbig, cfmws->hbig / MiB);
	printf(", qtag id %d", cfmws->qtag_id);
	printf(", NIW %d", (cfmws->record_length - 0x24) / 4);
	/* TODO: display more */
	printf(", ...\n");
}

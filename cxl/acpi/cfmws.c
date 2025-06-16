#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "cfmws.h"

struct cfmws *read_and_alloc_cfmws(FILE *fp)
{
	struct cfmws cfmws, *ptr;
	fpos_t old_pos;

	fgetpos(fp, &old_pos);
	fread(&cfmws, sizeof(struct cfmws), 1, fp);
	ptr = malloc(cfmws.record_length);
	fsetpos(fp, &old_pos);
	fread(ptr, cfmws.record_length, 1, fp);

	return ptr;
}

void display_cfmws(struct cfmws *cfmws)
{
	printf("CFMWS type %d, len %d, hpa %x, winsize %d, ENIW %d",
		cfmws->type, cfmws->record_length, cfmws->base_hpa,
		cfmws->window_size, cfmws->eniw);
	printf(", hbig %x", cfmws->hbig, cfmws->qtag_id);
	/* TODO: display more */
	printf(", ...\n");
}

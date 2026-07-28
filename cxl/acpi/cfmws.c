// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "cfmws.h"
#include "constants.h"

void display_cfmws(struct cfmws *cfmws)
{
	int niw;

	printf("---------------- CFMWS ----------------\n");
#ifdef DEBUG
	printf("struct cfmws size %ld\n", sizeof(struct cfmws));
#endif
	printf("CFMWS type %d, record length %d(0x%x), Base HPA 0x%lx, ",
	       cfmws->type, cfmws->record_length, cfmws->record_length,
	       cfmws->base_hpa);
	printf("winsize %ld(%ld MiB, %ld GiB), ", cfmws->window_size,
	       cfmws->window_size / MiB, cfmws->window_size / GiB);
	printf("ENIW %d, ", cfmws->eniw);
	printf("Interleave Arithmetic %d", cfmws->interleave_arithmetic);
	printf(", hbig 0x%x (%d MB)", cfmws->hbig, cfmws->hbig / MiB);
	printf(", qtag id %d", cfmws->qtag_id);

	niw = (cfmws->record_length - 0x24) / 4;

	/**
	 * CXL 3.0 Specification, Section 9.17.1.3, Table 9-22.
	 */
	if ((cfmws->eniw < 8 && niw != 1 << cfmws->eniw) ||
	    (cfmws->eniw >= 8 && niw != 3 * 1 << (cfmws->eniw - 8)))
		fprintf(stderr, "ERROR: Bad record length.\n");

	printf(", NIW %d", niw);

	if (cfmws->interleave_arithmetic == 0) {
	} else if (cfmws->interleave_arithmetic == 1) {
	}

	/* TODO: display more */
	printf(", ...\n");
}

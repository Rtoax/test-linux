// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "cedt.h"
#include "cfmws.h"
#include "constants.h"

/**
 * CXL 3.0 Specification, 8.2.4.19.7 CXL HDM Decoder n Control Register (Offset 20h*n+20h)
 * - Interleave Granularity size: 256, 512, 1k, 2k, 4k, 8k, 16k
 */
static const char *hbig_str(uint32_t hbig)
{
	switch (hbig) {
	case 0:
		return "256B";
	case 1:
		return "512B";
	case 2:
		return "1K";
	case 3:
		return "2K";
	case 4:
		return "4K";
	case 5:
		return "8K";
	case 6:
		return "16K";
	default:
		return "Unknown-Size";
	}
}

void display_cfmws(struct cfmws *cfmws, bool with_title)
{
	int niw;

	if (with_title)
		printf("\033[1;3;7mCFMWS (CXL Fixed Memory Window Structure)\033[m\n");
#ifdef DEBUG
	printf("struct cfmws size %ld\n", sizeof(struct cfmws));
#endif
	if (cfmws->type != CEDT_STRUCTURE_TYPE_CFMWS) {
		fprintf(stderr, "ERROR: CFMWS type is not %d.\n",
			CEDT_STRUCTURE_TYPE_CFMWS);
		exit(EXIT_FAILURE);
	}
	printf("CFMWS: record length %d(0x%x), Base HPA 0x%lx, ",
	       cfmws->record_length, cfmws->record_length, cfmws->base_hpa);
	printf("winsize %ld(%ld MiB, %ld GiB), ", cfmws->window_size,
	       cfmws->window_size / MiB, cfmws->window_size / GiB);
	printf("ENIW %d, ", cfmws->eniw);
	printf("Interleave Arithmetic %d", cfmws->interleave_arithmetic);
	printf(", hbig 0x%x (Interleave Granularity %s)", cfmws->hbig,
	       hbig_str(cfmws->hbig));
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

// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#include <stdio.h>
#include <stdlib.h>
#include "cedt.h"
#include "chbs.h"

void display_chbs(struct chbs *chbs)
{
	printf("---------------- CHBS ----------------\n");
#ifdef DEBUG
	printf("struct chbs size %ld\n", sizeof(struct chbs));
#endif
	if (chbs->type != CEDT_STRUCTURE_TYPE_CHBS) {
		fprintf(stderr, "ERROR: chbs type is not %d.\n",
			CEDT_STRUCTURE_TYPE_CHBS);
		exit(EXIT_FAILURE);
	}
	printf("CHBS: len %d, uid %x, CXL version %x, base %lx len %lx\n",
	       chbs->record_length, chbs->uid, chbs->cxl_version, chbs->base,
	       chbs->length);
}

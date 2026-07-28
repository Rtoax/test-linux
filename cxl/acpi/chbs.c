// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao
#include <stdio.h>
#include "chbs.h"

void display_chbs(struct chbs *chbs)
{
	printf("---------------- CHBS ----------------\n");
#ifdef DEBUG
	printf("struct chbs size %ld\n", sizeof(struct chbs));
#endif
	printf("CHBS type %d, len %d, uid %x, CXL version %x, base %lx len %lx\n",
		chbs->type, chbs->record_length, chbs->uid,
		chbs->cxl_version, chbs->base, chbs->length);
}

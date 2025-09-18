// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdlib.h>
#include "debug.h"


bool fakecuda_debug = false;
bool fakecuda_dump = false;


void __attribute__((constructor)) __attribute__((visibility("default")))
_fakecuda_start(void)
{
	if (atoi(getenv("FAKECUDA_DEBUG") ?: "0"))
		fakecuda_debug = 1;
	if (atoi(getenv("FAKECUDA_DUMP") ?: "0"))
		fakecuda_dump = 1;
}

// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao. All rights reserved. */
#include "rand.hpp"


curandStatus_t curandGetVersion(int *version)
{
	*version = 10;
	return CURAND_STATUS_SUCCESS;
}

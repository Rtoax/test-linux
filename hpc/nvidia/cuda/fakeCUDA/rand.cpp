// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include "rand.hpp"


curandStatus_t curandGetVersion(int *version)
{
	*version = 10;
	return CURAND_STATUS_SUCCESS;
}

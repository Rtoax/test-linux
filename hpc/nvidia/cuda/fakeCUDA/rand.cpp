// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "rand.hpp"


curandStatus_t curandGetVersion(int *version)
{
	*version = 10;
	return CURAND_STATUS_SUCCESS;
}

// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <math.h>
#include <string.h>
#include "solver.hpp"
#include "debug.h"

cusolverStatus_t cusolverGetVersion(int *version)
{
	*version = 12000;
	return CUSOLVER_STATUS_SUCCESS;
}

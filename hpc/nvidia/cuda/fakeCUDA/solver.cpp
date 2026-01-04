// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <math.h>
#include <string.h>
#include "solver.hpp"
#include "debug.h"

cusolverStatus_t cusolverGetVersion(int *version)
{
	*version = 12000;
	return CUSOLVER_STATUS_SUCCESS;
}

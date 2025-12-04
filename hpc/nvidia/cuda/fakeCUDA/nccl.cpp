// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "nccl.hpp"


ncclResult_t ncclGetVersion(int *version)
{
	*version = 21605;
	return ncclSuccess;
}

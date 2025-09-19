// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "hccl.hpp"


hcclResult_t hcclGetVersion(int *version)
{
	*version = 21605;
	return hcclSuccess;
}

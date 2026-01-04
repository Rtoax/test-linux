// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#pragma once

#ifndef likely
# define likely(x)    __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
# define unlikely(x)  __builtin_expect(!!(x), 0)
#endif

#define NCCL_CHECK(CALL, ERROR_DO)	{				\
	ncclResult_t __err = CALL;					\
	if (unlikely(__err != ncclSuccess)) {				\
		fprintf(stderr, "\033[31m");				\
		fprintf(stderr, "ERROR: %s:%d Call %s failed, %s\n",	\
			__func__, __LINE__,				\
			#CALL, ncclGetErrorString(__err));		\
		fprintf(stderr, "\033[m");				\
		ERROR_DO;						\
	}								\
}
#define NCCL_CHECK_EXIT(CALL) NCCL_CHECK(CALL, exit(-1))

// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2023-2026 Rong Tao. All rights reserved. */
#include <malloc.h>
#include <stdlib.h>
#include "oom.h"

void *glibc_alloc(size_t size)
{
	return malloc(size);
}

void glibc_free(void *mem, size_t size)
{
	free(mem);
}

struct oom_operations glibc_ops = {
	.name = "GLIBC",
	.total_size = 0,
	.alloc = glibc_alloc,
	.pagefault = default_pagefault,
	.free = glibc_free,
};

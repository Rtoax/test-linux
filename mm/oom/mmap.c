// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2023-2026 Rong Tao. All rights reserved. */
#include <malloc.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "oom.h"

static void *mmap_anon_alloc(size_t size)
{
	return mmap(NULL, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

static void mmap_anon_free(void *mem, size_t size)
{
	munmap(mem, size);
}

struct oom_operations mmap_anon_ops = {
	.name = "MMAP ANON",
	.total_size = 0,
	.alloc = mmap_anon_alloc,
	.pagefault = default_pagefault,
	.free = mmap_anon_free,
};

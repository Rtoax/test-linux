// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2023-2026 Rong Tao. All rights reserved. */
#pragma once
#include <stdbool.h>
#include <sys/types.h>

enum ops_type {
	OP_GLIBC = 1,
	OP_MMAP_ANON,
	OP_MMAP_FILE,
};

struct oom_operations {
	const char *name;
	size_t total_size;
	void *(*alloc)(size_t size);
	void (*pagefault)(void *mem, size_t size, bool pf_verbose);
	void (*free)(void *mem, size_t size);
};

extern struct oom_operations glibc_ops;
extern struct oom_operations mmap_anon_ops;

void default_pagefault(void *mem, size_t size, bool pf_verbose);

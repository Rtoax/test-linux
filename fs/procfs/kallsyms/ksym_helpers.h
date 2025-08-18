// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <stdbool.h>
#include <sys/types.h>

#define INVALID_ADDR	(-1)

struct ksym;
struct ksyms;

struct ksyms *load_kallsyms(void);
void free_kallsyms(struct ksyms *ksyms);

/**
 * If exist, return valid address, else return INVALID_ADDR
 */
long ksym_addr(const char *name, const char *kmod);

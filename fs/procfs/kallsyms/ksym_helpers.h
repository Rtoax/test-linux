// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <stdbool.h>
#include <sys/types.h>

#define INVALID_ADDR	(-1)

int load_kallsyms(void);

/**
 * If exist, return valid address, else return INVALID_ADDR
 */
long ksym_addr(const char *name);

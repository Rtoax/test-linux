// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025 Rong Tao */
#pragma once

#define STACK_MAX_DEPTH	127

#ifdef __USER__
#include "ksym_helpers.h"
void init_stackmap(struct bpf_map *stackmap, size_t size);
void print_stack(int stack_map_fd, struct ksyms *ksyms);
#endif

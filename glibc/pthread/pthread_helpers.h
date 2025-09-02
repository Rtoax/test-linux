// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024-2025 Rong Tao */
#pragma once
#include <pthread.h>

pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg);
int sys_affinity_bind(int cpu);

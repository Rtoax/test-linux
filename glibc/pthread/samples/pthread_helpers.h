// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <pthread.h>

pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg);

// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2024-2026 Rong Tao. All rights reserved. */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg)
{
	pthread_t thread;
	pthread_attr_t attr, *pattr = NULL;
	cpu_set_t cpuset;

	pthread_attr_init(&attr);

	if (cpu >= 0) {
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);
		/**
		 * Replace with pthread_setaffinity_np() for musl-libc.
		 *
		 * The _np suffix in the function name of
		 * pthread_attr_setaffinity_np stands for "non-portable" and is
		 * part of the GNU extension, not included in the POSIX
		 * standard. One of the design goals of musl libc was to keep it
		 * lean and compliant with standards, so it refused to implement
		 * many of the extensions specific to this glibc. Alpine Linux's
		 * package build script also explicitly states that
		 * pthread_attr_setaffinity_np is "glibcism not in POSIX
		 * standard" and is therefore not supported in musl.
		 */
		pthread_attr_setaffinity_np(&attr, sizeof(cpuset), &cpuset);
		pattr = &attr;
	}

	if (pthread_create(&thread, pattr, routine, arg) != 0) {
		printf("Failed to start thread\n");
		exit(1);
	}

	pthread_attr_destroy(&attr);

	return thread;
}

void *routine(void *arg)
{
	return NULL;
}

int main(void)
{
	pthread_t thread = start_thread(routine, 0, NULL);
	pthread_json(thread, NULL);
}

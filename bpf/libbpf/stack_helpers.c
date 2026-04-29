// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdlib.h>
#include <malloc.h>
#include <linux/bpf.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#define __USER__
#include "stack_helpers.h"

/* init stackmap */
void init_stackmap(struct bpf_map *stackmap, size_t size)
{
	bpf_map__set_value_size(stackmap,
			sizeof(unsigned long) * STACK_MAX_DEPTH);
	bpf_map__set_max_entries(stackmap, 1024);
}

void print_stack(int stack_map_fd, struct ksyms *ksyms)
{
	int id, next_id, i;
	unsigned long *IPs;

	id = 0;
	IPs = malloc(sizeof(unsigned long) * STACK_MAX_DEPTH);

	while (bpf_map_get_next_key(stack_map_fd, &id, &next_id) == 0) {
		bpf_map_lookup_elem(stack_map_fd, &next_id, IPs);
		printf("-----------\n");
		for (i = 0; i < STACK_MAX_DEPTH && IPs[i]; i++) {
			unsigned long off = 0;
			const char *name = ksym_name(ksyms, IPs[i], &off);
			printf("\t%#016lx %s", IPs[i], name ?: "[unknown]");
			if (off > 0)
				printf("+0x%lx\n", off);
			else if (off < 0)
				printf("-0x%lx\n", -off);
			else
				printf("\n");
		}
		id = next_id;
	}

	free(IPs);
}

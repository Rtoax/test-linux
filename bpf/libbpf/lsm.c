// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2024 David Di */
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "lsm.skel.h"
#include "trace_helpers.h"

static volatile sig_atomic_t stop = 0;
static sigjmp_buf jmp;

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	stop = 1;
	siglongjmp(jmp, 1);
}

/**
 * Notice: Ensure your kernel version is 5.7 or higher, BTF (BPF Type Format)
 * is enabled, and the file '/sys/kernel/security/lsm' includes 'bpf'.
 */
static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	return vfprintf(stderr, format, args);
}

int main(int argc, char **argv)
{
	struct lsm_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);
	sigsetjmp(jmp, 1);
	if (stop)
		goto cleanup;

	/* Set up libbpf errors and debug info callback */
	libbpf_set_print(libbpf_print_fn);

	/* Open, load, and verify BPF application */
	skel = lsm_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open and load BPF skeleton\n");
		goto cleanup;
	}

	/* Attach lsm handler */
	err = lsm_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	lsm_bpf__destroy(skel);
	return -err;
}

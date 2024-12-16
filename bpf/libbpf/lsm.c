// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2024 David Di */
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "trace_helpers.h"
#if defined(LSM_BPF)
# pragma message "Compile lsm/bpf"
#include "lsm_bpf.skel.h"
#define struct_bpf	lsm_bpf_bpf
#define _bpf__open_and_load	lsm_bpf_bpf__open_and_load
#define _bpf__attach	lsm_bpf_bpf__attach
#define _bpf__destroy	lsm_bpf_bpf__destroy
#elif defined(LSM_SOCKET_CREATE)
# pragma message "Compile lsm/socket_create"
#include "lsm_socket_create.skel.h"
#define struct_bpf	lsm_socket_create_bpf
#define _bpf__open_and_load	lsm_socket_create_bpf__open_and_load
#define _bpf__attach	lsm_socket_create_bpf__attach
#define _bpf__destroy	lsm_socket_create_bpf__destroy
#else
#error "Not defined LSM_BPF"
#endif

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
	struct struct_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);
	sigsetjmp(jmp, 1);
	if (stop)
		goto cleanup;

	/* Set up libbpf errors and debug info callback */
	libbpf_set_print(libbpf_print_fn);

	/* Open, load, and verify BPF application */
	skel = _bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open and load BPF skeleton\n");
		goto cleanup;
	}

	/* Attach lsm handler */
	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	_bpf__destroy(skel);
	return -err;
}

// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2024 David Di */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#if defined(LSM_BPF)
# pragma message "Compile lsm/bpf"
#include "lsm_bpf.skel.h"
#define NAME lsm_bpf
#include "skel_defs.h"
#elif defined(LSM_SOCKET_CREATE)
# pragma message "Compile lsm/socket_create"
#include "lsm_socket_create.skel.h"
#define NAME lsm_socket_create
#include "skel_defs.h"
#elif defined(LSM_SOCKET_SENDMSG)
# pragma message "Compile lsm/socket_sendmsg"
#include "lsm_socket_sendmsg.skel.h"
#define NAME lsm_socket_sendmsg
#include "skel_defs.h"
#elif defined(LSM_FILE_OPEN)
# pragma message "Compile lsm/file_open"
#include "lsm_file_open.skel.h"
#define NAME lsm_file_open
#include "skel_defs.h"
#else
#error "Not defined LSM_BPF, LSM_SOCKET_CREATE, LSM_SOCKET_SENDMSG, LSM_FILE_OPEN"
#endif

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	read_trace_pipe_stop();
}

/**
 * Notice: Ensure your kernel version is 5.7 or higher, BTF (BPF Type Format)
 * is enabled, and the file '/sys/kernel/security/lsm' includes 'bpf'.
 */

int main(int argc, char **argv)
{
	struct struct_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);

	/* Set up libbpf errors and debug info callback */
	libbpf_set_print(libbpf_print_fn);

	skel = BPF__OPEN_AND_LOAD(_bpf__open_and_load, _bpf__open_opts,
			_bpf__load, _bpf__destroy);

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

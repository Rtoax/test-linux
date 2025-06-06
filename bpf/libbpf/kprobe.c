// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#if defined(KPROBE)
#include "kprobe.skel.h"
#define struct_bpf	kprobe_bpf
#define _bpf__open_and_load	kprobe_bpf__open_and_load
#define _bpf__attach	kprobe_bpf__attach
#define _bpf__destroy	kprobe_bpf__destroy
#elif defined(FENTRY)
#include "fentry.skel.h"
#define struct_bpf	fentry_bpf
#define _bpf__open_and_load	fentry_bpf__open_and_load
#define _bpf__attach	fentry_bpf__attach
#define _bpf__destroy	fentry_bpf__destroy
#elif defined(FMOD_RET)
#include "fmod_ret.skel.h"
#define struct_bpf	fmod_ret_bpf
#define _bpf__open_and_load	fmod_ret_bpf__open_and_load
#define _bpf__attach	fmod_ret_bpf__attach
#define _bpf__destroy	fmod_ret_bpf__destroy
#else
#error "Not support skel"
#endif

void sig_handler(int sig)
{
	read_trace_pipe_stop();
}

int main(int argc, char **argv)
{
	struct struct_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);

	libbpf_set_print(libbpf_print_fn);

	skel = _bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n");
		return 1;
	}

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

// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2023 Meta */
#include <argp.h>
#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <unistd.h>
#include "iter_task.h"
#if defined(ITER_TASK)
#include "iter_task.skel.h"
#define struct_bpf	iter_task_bpf
#define _bpf__open_and_load	iter_task_bpf__open_and_load
#define _bpf__attach	iter_task_bpf__attach
#define _bpf__destroy	iter_task_bpf__destroy
#define _bpf_link	get_tasks
#elif defined(ITER_TASK_FILE)
#include "iter_task_file.skel.h"
#define struct_bpf	iter_task_file_bpf
#define _bpf__open_and_load	iter_task_file_bpf__open_and_load
#define _bpf__attach	iter_task_file_bpf__attach
#define _bpf__destroy	iter_task_file_bpf__destroy
#define _bpf_link	dump_task_file
#endif


static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level == LIBBPF_DEBUG)
		return 0;
	return vfprintf(stderr, format, args);
}

static volatile bool exiting = false;

static void sig_handler(int sig)
{
	exiting = true;
}

static const char *get_task_state(__u32 state)
{
	/* Taken from:
	 * https://elixir.bootlin.com/linux/latest/source/include/linux/sched.h#L85
	 * There are a lot more states not covered here but these are common ones.
	 */
	switch (state) {
	case 0x0000: return "RUNNING";
	case 0x0001: return "INTERRUPTIBLE";
	case 0x0002: return "UNINTERRUPTIBLE";
	case 0x0200: return "WAKING";
	case 0x0400: return "NOLOAD";
	case 0x0402: return "IDLE";
	case 0x0800: return "NEW";
	default: return "<unknown>";
	}
}

int main(int argc, char **argv)
{
	struct struct_bpf *skel;
	int iter_fd;
	ssize_t ret;
	int err;

	/* Set up libbpf errors and debug info callback */
	libbpf_set_print(libbpf_print_fn);

	/* Cleaner handling of Ctrl-C */
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	/* Open, load, and verify BPF application */
	skel = _bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open and load BPF skeleton\n");
		goto cleanup;
	}

	/* Attach tracepoints */
	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	iter_fd = bpf_iter_create(bpf_link__fd(skel->links._bpf_link));
	if (iter_fd < 0) {
		err = -1;
		fprintf(stderr, "Failed to create iter\n");
		goto cleanup;
	}

	while (true) {
#if defined(ITER_TASK)
		struct task_info buf;

		ret = read(iter_fd, &buf, sizeof(struct task_info));
		if (ret < 0) {
			if (errno == EAGAIN)
				continue;
			err = -errno;
			break;
		}
		if (ret == 0)
			break;
		if (buf.kstack_len <= 0) {
			printf("Error getting kernel stack for task. Task Info. Pid: %d. Process Name: %s. Kernel Stack Error: %d. State: %s\n",
			       buf.pid, buf.comm, buf.kstack_len, get_task_state(buf.state));
		} else {
			printf("Task Info. Pid: %d. Process Name: %s. Kernel Stack Len: %d. State: %s\n",
			       buf.pid, buf.comm, buf.kstack_len, get_task_state(buf.state));
		}
#elif defined(ITER_TASK_FILE)
		struct task_file_info buf;

		ret = read(iter_fd, &buf, sizeof(struct task_file_info));
		if (ret < 0) {
			if (errno == EAGAIN)
				continue;
			err = -errno;
			break;
		}
		if (ret == 0)
			break;
		printf("Task File Info, Pid: %d. Process Name: %s. Fd %d.\n",
			buf.pid, buf.comm, buf.fd);
#endif
	}

cleanup:
	/* Clean up */
	close(iter_fd);
	_bpf__destroy(skel);

	return err < 0 ? -err : 0;
}

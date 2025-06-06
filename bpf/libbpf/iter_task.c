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

#include "iter.h"
#include "task_helpers.h"
#include "trace_helpers.h"
#include "libbpf_wrapper.h"

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
#elif defined(ITER_TASK_VMA)
#include "iter_task_vma.skel.h"
#define struct_bpf	iter_task_vma_bpf
#define _bpf__open_and_load	iter_task_vma_bpf__open_and_load
#define _bpf__attach	iter_task_vma_bpf__attach
#define _bpf__destroy	iter_task_vma_bpf__destroy
#define _bpf_link	dump_task_vma
#elif defined(ITER_BPF_MAP)
#include "iter_bpf_map.skel.h"
#define struct_bpf	iter_bpf_map_bpf
#define _bpf__open_and_load	iter_bpf_map_bpf__open_and_load
#define _bpf__attach	iter_bpf_map_bpf__attach
#define _bpf__destroy	iter_bpf_map_bpf__destroy
#define _bpf_link	dump_bpf_map
#elif defined(ITER_KMEM_CACHE)
#include "iter_kmem_cache.skel.h"
#define struct_bpf	iter_kmem_cache_bpf
#define _bpf__open_and_load	iter_kmem_cache_bpf__open_and_load
#define _bpf__attach	iter_kmem_cache_bpf__attach
#define _bpf__destroy	iter_kmem_cache_bpf__destroy
#define _bpf_link	dump_kmem_cache
#else
# error Must define iter type!!!!
#endif


static volatile bool exiting = false;

static void sig_handler(int sig)
{
	exiting = true;
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
#elif defined(ITER_TASK_FILE)
		struct task_file_info buf;
		ret = read(iter_fd, &buf, sizeof(struct task_file_info));
#elif defined(ITER_TASK_VMA)
		struct task_vma_info buf;
		ret = read(iter_fd, &buf, sizeof(struct task_vma_info));
#elif defined(ITER_BPF_MAP)
		struct iter_bpf_map_info buf;
		ret = read(iter_fd, &buf, sizeof(struct iter_bpf_map_info));
#elif defined(ITER_KMEM_CACHE)
		struct iter_kmem_cache_info buf;
		ret = read(iter_fd, &buf, sizeof(struct iter_kmem_cache_info));
#endif
		if (ret < 0) {
			if (errno == EAGAIN)
				continue;
			err = -errno;
			break;
		}
		if (ret == 0)
			break;
#if defined(ITER_TASK)
		if (buf.kstack_len <= 0) {
			printf("Error getting kernel stack for task. Task Info. Pid: %d. Process Name: %s. Kernel Stack Error: %d. State: %s\n",
			       buf.pid, buf.comm, buf.kstack_len, get_task_state(buf.state));
		} else {
			printf("Task Info. Pid: %d. Process Name: %s. Kernel Stack Len: %d. State: %s\n",
			       buf.pid, buf.comm, buf.kstack_len, get_task_state(buf.state));
		}
#elif defined(ITER_TASK_FILE)
		printf("Task File Info, Pid: %d. Process Name: %s. Fd %d.\n",
			buf.pid, buf.comm, buf.fd);
#elif defined(ITER_TASK_VMA)
		printf("Task VMA Info, Pid: %d. Process Name: %s. vm %lx~%lx.\n",
			buf.pid, buf.comm, buf.vm_start, buf.vm_end);
#elif defined(ITER_BPF_MAP)
		printf("BPF Map Info, Pid: %d. Process Name: %s. map type:%d id:%d.\n",
			buf.pid, buf.comm, buf.map_type, buf.map_id);
#elif defined(ITER_KMEM_CACHE)
		printf("kmem_cache %s: size: %d.\n", buf.name, buf.size);
#endif
	}

cleanup:
	/* Clean up */
	close(iter_fd);
	_bpf__destroy(skel);

	return err < 0 ? -err : 0;
}

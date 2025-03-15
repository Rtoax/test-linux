/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */
/* Copyright (c) 2024 Rong Tao */
/* Copyright (c) 2023 Meta */

#define TASK_COMM_LEN 16
#define MAX_STACK_LEN 127

/**
 * struct bpf_iter__task {}
 */
struct task_info {
	pid_t pid;
	pid_t tid;
	__u32 state;
	char comm[TASK_COMM_LEN];
	int kstack_len;
	__u64 kstack[MAX_STACK_LEN];
};

/**
 * struct bpf_iter__task_file {}
 */
struct task_file_info {
	pid_t pid;
	pid_t tid;
	int fd;
	char comm[TASK_COMM_LEN];
};

/**
 * struct bpf_iter__task_vma {}
 */
struct task_vma_info {
	pid_t pid;
	pid_t tid;
	char comm[TASK_COMM_LEN];
	unsigned long vm_start, vm_end;
};

/**
 * struct bpf_iter__bpf_map {}
 */
struct iter_bpf_map_info {
	pid_t pid;
	pid_t tid;
	char comm[TASK_COMM_LEN];
	enum bpf_map_type map_type;
	__u32 map_id;
};

/**
 * struct bpf_iter__kmem_cache {}
 */
struct iter_kmem_cache_info {
	unsigned int size;
};

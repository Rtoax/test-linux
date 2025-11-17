/**
 * void *bpf_cgrp_storage_get(struct bpf_map *map, struct cgroup *cgroup, void *value, u64 flags);
 */
#include "vmlinux.h"

void test(void)
{
	bpf_cgrp_storage_get(0, 0, 0, 0);
}

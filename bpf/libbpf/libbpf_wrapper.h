#pragma once
#include <bpf/bpf.h>
#include <bpf/libbpf.h>

int libbpf_bpf_xdp_attach(int ifindex, int prog_fd, int xdp_flags);
int libbpf_bpf_xdp_detach(int ifindex, int xdp_flags);

struct perf_buffer *libbpf_perf_buffer__new(int map_fd,
					    size_t page_cnt,
					    perf_buffer_sample_fn sample_cb,
					    perf_buffer_lost_fn lost_cb);

int libbpf_bpf_map_update_elem(const struct bpf_map *map, const void *key,
			       size_t key_sz, const void *value, size_t value_sz,
			       __u64 flags);

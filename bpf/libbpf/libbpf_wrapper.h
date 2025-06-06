#pragma once
#include <bpf/bpf.h>
#include <bpf/libbpf.h>

/**
 * Failed add _bpf__open_and_load_opts()
 * https://lore.kernel.org/lkml/tencent_FB1D31D70047E82DCBF3D257C5ED75653405@qq.com/
 *
 * So, let's add a macro.
 */
#if defined(LIBBPF_OPTS)
#define BPF__OPEN_AND_LOAD(skel, open_and_load, open_opts, load, destroy)	\
	char log_buf[64 * 1024];						\
	LIBBPF_OPTS(bpf_object_open_opts, ___opts,				\
		.kernel_log_buf = log_buf,					\
		.kernel_log_size = sizeof(log_buf),				\
		.kernel_log_level = LIBBPF_DEBUG,				\
	);									\
										\
	skel = open_opts(&___opts);						\
	err = load(skel);							\
	if (err) {								\
		printf("Failed to load BPF object\n");				\
		destroy(skel);							\
		return 1;							\
	}									\
	if (!skel) {								\
		printf("Failed to open BPF object\n");				\
		return 1;							\
	}									\
	libbpf_print_bpf_log_buf(log_buf, sizeof(log_buf));
#else
#define BPF__OPEN_AND_LOAD(skel, open_and_load, open_opts, load, destroy)	\
	skel = open_and_load();							\
	if (!skel) {								\
		printf("Failed to open BPF object\n");				\
		return 1;							\
	}
#endif

int libbpf_bpf_xdp_attach(int ifindex, int prog_fd, int xdp_flags);
int libbpf_bpf_xdp_detach(int ifindex, int xdp_flags);

struct perf_buffer *libbpf_perf_buffer__new(int map_fd,
					    size_t page_cnt,
					    perf_buffer_sample_fn sample_cb,
					    perf_buffer_lost_fn lost_cb);

int libbpf_bpf_map_update_elem(const struct bpf_map *map, const void *key,
			       size_t key_sz, const void *value, size_t value_sz,
			       __u64 flags);

int libbpf_print_bpf_log_buf(char *buf, size_t size);

int libbpf_print_fn(enum libbpf_print_level level, const char *format,
		    va_list args);

// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "libbpf_wrapper.h"


int tl_bpf_xdp_attach(int ifindex, int prog_fd, int xdp_flags)
{
	int err;
/**
 * libbpf commit e8802d6319ab ("libbpf: remove deprecated XDP APIs") remove
 * bpf_set_link_xdp_fd(), libbpf version v1.0.0
 */
#if LIBBPF_MAJOR_VERSION >= 1
	err = bpf_xdp_attach(ifindex, prog_fd, xdp_flags, NULL);
#else
	err = bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags);
#endif
	if (err < 0) {
		printf("attach xdp fd %d to ifindex %d failed\n", prog_fd,
			ifindex);
	}

	return err;
}

/**
 * Like: sudo bpftool net detach xdp dev $interface
 */
int tl_bpf_xdp_detach(int ifindex, int xdp_flags)
{
	int err;
/**
 * libbpf commit e8802d6319ab ("libbpf: remove deprecated XDP APIs") remove
 * bpf_set_link_xdp_fd(), libbpf version v1.0.0
 */
#if LIBBPF_MAJOR_VERSION >= 1
	err = bpf_xdp_detach(ifindex, xdp_flags, NULL);
#else
	err = bpf_set_link_xdp_fd(ifindex, -1, xdp_flags);
#endif
	return err;
}

struct perf_buffer *tl_perf_buffer__new(int map_fd,
					size_t page_cnt,
					perf_buffer_sample_fn sample_cb,
					perf_buffer_lost_fn lost_cb)
{
	struct perf_buffer *pb = NULL;
#if LIBBPF_MAJOR_VERSION >= 1
	pb = perf_buffer__new(map_fd, 8, sample_cb, lost_cb, NULL,
			      NULL);
#else
	struct perf_buffer_opts pb_opts;
	pb_opts.sample_cb = sample_cb;
	pb_opts.lost_cb = lost_cb;
	pb = perf_buffer__new(map_fd, 8, &pb_opts);
#endif
	return pb;
}

int tl_bpf_map_update_elem(const struct bpf_map *map, const void *key,
			   size_t key_sz, const void *value, size_t value_sz,
			   __u64 flags)
{
	int fd, err = 0;
/**
 * libbpf commit 650adc5118f1 ("libbpf: Add safer high-level wrappers for map
 * operations") support bpf_map__update_elem()
 */
#if LIBBPF_MAJOR_VERSION >= 1 || (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 8)
	err = bpf_map__update_elem(map, key, key_sz, value, value_sz, flags);
#else
	fd = bpf_map__fd(map);
	err = bpf_map_update_elem(fd, key, msg, flags);
#endif
	if (err < 0)
		fprintf(stderr, "failed to update elem.\n");
	return err;
}

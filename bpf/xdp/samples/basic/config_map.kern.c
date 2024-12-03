#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>

struct config {
	__u32 action;
	int ifindex;
	__u32 options;
};

struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__type(key, int);
	__type(value, struct config);
	__uint(max_entries, 1);
} config_map SEC(".maps");

SEC("xdp_prog0")
int  xdp_prognum0(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data     = (void *)(long)ctx->data;
	struct config *config;
	u32 key = 0;

	config = bpf_map_lookup_elem(&config_map, &key);
	if (!config)
		return XDP_ABORTED;

	return XDP_PASS;
}

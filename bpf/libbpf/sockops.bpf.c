/**
 * BPF_PROG_TYPE_SOCK_OPS
 *
 * Socket ops programs are attached to cGroups and get called for multiple
 * lifecycle events of a socket, giving the program the opportunity to changes
 * settings per connection or to record the existence of a socket.
 *
 * see linux/tools/testing/selftests/bpf/progs/test_tcp_hdr_options.c
 */
#include <vmlinux.h>
#include <linux/version.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define CG_OK	1
#define CG_ERR	0

SEC("sockops")
int _sockops(struct bpf_sock_ops *skops)
{
	switch (skops->op) {
/**
 * v4.18-rc3-587-gf333ee0cdb27
 * linux commit f333ee0cdb27 ("bpf: Add BPF_SOCK_OPS_TCP_LISTEN_CB")
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 18, 0)
	case BPF_SOCK_OPS_TCP_LISTEN_CB:
		bpf_printk("BPF_SOCK_OPS_TCP_LISTEN_CB");
		break;
#endif
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		bpf_printk("BPF_SOCK_OPS_TCP_CONNECT_CB");
		break;
/**
 * v5.9-rc1-156-g0813a841566f
 * linux commit 0813a841566f ("bpf: tcp: Allow bpf prog to write and parse TCP header option")
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)
	case BPF_SOCK_OPS_PARSE_HDR_OPT_CB:
		bpf_printk("BPF_SOCK_OPS_PARSE_HDR_OPT_CB");
		break;
	case BPF_SOCK_OPS_HDR_OPT_LEN_CB:
		bpf_printk("BPF_SOCK_OPS_HDR_OPT_LEN_CB");
		break;
	case BPF_SOCK_OPS_WRITE_HDR_OPT_CB:
		bpf_printk("BPF_SOCK_OPS_WRITE_HDR_OPT_CB");
		break;
#endif
	case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		bpf_printk("BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB");
		break;
	case BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		bpf_printk("BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB");
		break;
	}

	return CG_OK;
}

char __license[] SEC("license") = "GPL";

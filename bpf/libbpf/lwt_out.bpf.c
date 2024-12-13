/**
 * BPF_PROG_TYPE_LWT_OUT
 *
 * LWT (Light Weight Tunnel) Output programs attach to the egress path of a
 * light weight tunnel.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>


SEC("lwt_out")
void packet_lwt_out(void)
{
}

char _license[] SEC("license") = "GPL";

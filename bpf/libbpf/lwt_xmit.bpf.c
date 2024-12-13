/**
 * BPF_PROG_TYPE_LWT_XMIT
 *
 * Extension programs can be used to dynamically extend another BPF program.
 */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>

SEC("lwt_xmit")
void packet_lwt_xmit(void)
{
}

char _license[] SEC("license") = "GPL";

/**
 * BPF_PROG_TYPE_TRACING fmod_ret BPF_MODIFY_RETURN
 */
#include <vmlinux.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_helpers.h>
#include "bpf_misc.h"

SEC("fmod_ret/" SYS_PREFIX "sys_getpgid")
int fmodret_sys_getpgid(void *ctx)
{
	return -22;
}

char _license[] SEC("license") = "GPL";

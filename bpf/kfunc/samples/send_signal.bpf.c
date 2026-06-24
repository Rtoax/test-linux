/**
 * static long (* const bpf_send_signal)(__u32 sig) = (void *) 109;
 *
 * - linux v5.2-rc1-220-g8b401f9ed244
 *   commit 8b401f9ed244 ("bpf: implement bpf_send_signal() helper")
 * - https://docs.ebpf.io/linux/helper-function/bpf_send_signal/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_send_signal(2 /* SIGINT */);
}

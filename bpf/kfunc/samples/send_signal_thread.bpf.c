/**
 * static long (* const bpf_send_signal_thread)(__u32 sig) = (void *) 117;
 *
 * - linux v5.5-rc4-897-g8482941f0906
 *   commit 8482941f0906 ("bpf: Add bpf_send_signal_thread() helper")
 * - https://docs.ebpf.io/linux/helper-function/bpf_send_signal_thread/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_send_signal_thread(2 /* SIGINT */);
}

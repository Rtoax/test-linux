#include <linux/if_ether.h>
#include <linux/ip.h>

int tcpconnect(void *ctx)
{
	bpf_trace_printk("tcp connect.\n");
	return 0;
}

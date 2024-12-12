#include <argp.h>
#include <arpa/inet.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sk_skb.skel.h"

int main(int argc, char *argv[])
{
	struct sk_skb_bpf *skel;
	int verdict;

	skel = sk_skb_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "open and load error\n");
		return -1;
	}

	verdict = bpf_program__fd(skel->progs.prog_skb_drop);

	(void)verdict;

	sk_skb_bpf__destroy(skel);
	return 0;
}

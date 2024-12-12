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
#include "sk_msg.skel.h"

int main(int argc, char *argv[])
{
	struct sk_msg_bpf *skel;
	int verdict;

	skel = sk_msg_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "open and load error\n");
		return -1;
	}

	verdict = bpf_program__fd(skel->progs.prog_skmsg_drop);

	(void)verdict;

	sk_msg_bpf__destroy(skel);
	return 0;
}

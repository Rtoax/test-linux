#include <argp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <net/if.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define BUFFER_MAX 2048

static const char *interface = NULL;
static int ifindex = 0;
static volatile sig_atomic_t exiting = 0;
int verbose = false;

const char argp_prog_doc[] =
	"USAGE: [-i <interface>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		interface = arg;
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

void sig_handler(int sig)
{
	psignal(sig, "tcpdump");
	exiting = 1;
	fflush(stdout);
	fflush(stderr);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	int err, sock, len;
	char buffer[BUFFER_MAX];
	struct sockaddr_ll sll;

	struct ethhdr *ethhdr;
	struct iphdr *iphdr;
	char *p;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	signal(SIGINT, sig_handler);

	/* Data Link Layer */
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock < 0 ) {
		perror("Create socket error");
		exit(0);
	}

	if (interface) {
		ifindex = if_nametoindex(interface);
		if (ifindex == 0) {
			fprintf(stderr, "Unknown interface %s\n", interface);
			exit(EXIT_FAILURE);
		}
	}

	if (ifindex > 0) {
		memset(&sll, 0, sizeof(sll));
		sll.sll_family = PF_PACKET;
		sll.sll_ifindex = if_nametoindex(interface);
		sll.sll_protocol = htons(ETH_P_ALL);
		err = bind(sock, (struct sockaddr *)&sll, sizeof(sll));
		if (err < 0) {
			fprintf(stderr, "bind %s: %m\n", interface);
			err = -errno;
			goto cleanup;
		}
	}

	printf("Tcpdump, hit ctrl-c to end.\n");
	printf("%-8s %-17s %-17s %-16s %-16s %-8s\n",
		"LEN", "SRC MAC", "DST MAC", "SRC IP", "DST IP", "PROTO");

	while (!exiting) {
		len = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
		if (len < sizeof(struct ethhdr)) {
			fprintf(stderr, "packet length error: %m.\n" );
			continue;
		}

		printf("%-8d ", len);

		ethhdr = (struct ethhdr *)buffer;
		iphdr = (struct iphdr *)(buffer + sizeof(struct ethhdr));

		printf("%02X:%02X:%02X:%02X:%02X:%02X ",
				(uint8_t)ethhdr->h_source[0],
				(uint8_t)ethhdr->h_source[1],
				(uint8_t)ethhdr->h_source[2],
				(uint8_t)ethhdr->h_source[3],
				(uint8_t)ethhdr->h_source[4],
				(uint8_t)ethhdr->h_source[5]);

		printf("%02X:%02X:%02X:%02X:%02X:%02X ",
				(uint8_t)ethhdr->h_dest[0],
				(uint8_t)ethhdr->h_dest[1],
				(uint8_t)ethhdr->h_dest[2],
				(uint8_t)ethhdr->h_dest[3],
				(uint8_t)ethhdr->h_dest[4],
				(uint8_t)ethhdr->h_dest[5]);

		p = (char*)&iphdr->saddr;
		char s_ip[16];
		sprintf(s_ip, "%d.%d.%d.%d ",
				(uint8_t)p[0],
				(uint8_t)p[1],
				(uint8_t)p[2],
				(uint8_t)p[3]);
		printf("%-16s ", s_ip);

		p = (char*)&iphdr->daddr;
		sprintf(s_ip, "%d.%d.%d.%d ",
				(uint8_t)p[0],
				(uint8_t)p[1],
				(uint8_t)p[2],
				(uint8_t)p[3]);
		printf("%-16s ", s_ip);

		switch(iphdr->protocol) {
		case IPPROTO_ICMP:
			printf("ICMP");
			break;
		case IPPROTO_IGMP:
			printf("IGMP");
			break;
		case IPPROTO_IPIP:
			printf("IPIP");
			break;
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_RAW:
			printf("RAW");
			break;
		default:
			printf("Unknown type");
			break;
		}
		printf("\n");
		fflush(stdout);
	}

cleanup:
	close(sock);
	return err;
}

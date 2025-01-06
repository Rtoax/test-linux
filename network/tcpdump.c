#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <arpa/inet.h>

#define BUFFER_MAX 2048

static volatile sig_atomic_t exiting = 0;

void sig_handler(int sig)
{
	psignal(sig, "tcpdump");
	exiting = 1;
}

int main(int argc, char *argv[])
{
	int  sock;
	char buffer[BUFFER_MAX];
	int len;

	struct ethhdr *ethhdr;
	struct iphdr *iphdr;
	char* p;

	signal(SIGINT, sig_handler);

	/* Data Link Layer */
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock < 0 ) {
		perror("Create socket error");
		exit(0);
	}

	printf("Tcpdump, hit ctrl-c to end.\n");
	printf("%-8s %-17s %-17s %-16s %-16s %-8s\n",
		"LEN", "SRC MAC", "DST MAC", "SRC IP", "DST IP", "PROTO");

	while (!exiting) {
		len = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
		if (len < 46) {
			printf("packet length error: %m.\n" );
			close(sock);
			exit(0);
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
	}

	close(sock);
	return 0;
}

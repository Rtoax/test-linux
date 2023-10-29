#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

#define BUFFER_MAX 2048

typedef int int32;
typedef unsigned int u_int32;
typedef unsigned char u_char;
typedef unsigned short u_short;

/* include/uapi/linux/if_ether.h: struct ethhdr {} */
struct eth_hdr {
	 char h_dest[6];
	 char h_source[6];
	 short h_proto;
} __attribute__((packed));

/* include/uapi/linux/ip.h: struct iphdr {} */
struct iphdr{
	#ifdef __LITTLE_ENDIAN_BIFIELD
		u_char ip_len:4, ip_ver:4;
	#else
		u_char ip_ver:4, ip_len:4;
	#endif
	u_char  tos;
	u_short total_len;
	u_short id;
	u_short flags_off;
	u_char  ttl;
	u_char  protocol;
	u_short check;
	u_int32 saddr;
	u_int32 daddr;
} __attribute__((packed));

int main(int argc, char *argv[])
{
	int  sock;
	char buffer[BUFFER_MAX];
	int len;

	struct eth_hdr *mac_hdr;
	struct iphdr *ip_hdr;
	char* p;

	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock < 0 ) {
		perror("Create socket error");
		exit(0);
	}

	printf("Tcpdump, hit ctrl-c to end.\n");
	printf("%-8s %-17s %-17s %-16s %-16s %-8s\n",
		"LEN", "SRC MAC", "DST MAC", "SRC IP", "DST IP", "PROTO");
	while (1) {
		len = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
		if (len < 46) {
			printf("Catch packet length error.\n" );
			close(sock);
			exit(0);
		}

		printf("%-8d ", len);

		mac_hdr = (struct eth_hdr *)buffer;
		ip_hdr = (struct iphdr *)(buffer + sizeof(struct ethhdr));

		printf("%02X:%02X:%02X:%02X:%02X:%02X ",
				(u_char)mac_hdr->h_source[0],
				(u_char)mac_hdr->h_source[1],
				(u_char)mac_hdr->h_source[2],
				(u_char)mac_hdr->h_source[3],
				(u_char)mac_hdr->h_source[4],
				(u_char)mac_hdr->h_source[5]
			);

		printf("%02X:%02X:%02X:%02X:%02X:%02X ",
				(u_char)mac_hdr->h_dest[0],
				(u_char)mac_hdr->h_dest[1],
				(u_char)mac_hdr->h_dest[2],
				(u_char)mac_hdr->h_dest[3],
				(u_char)mac_hdr->h_dest[4],
				(u_char)mac_hdr->h_dest[5]
			);

		p = (char*)&ip_hdr->saddr;
		char s_ip[16];
		sprintf(s_ip, "%d.%d.%d.%d ",
				(u_char)p[0],
				(u_char)p[1],
				(u_char)p[2],
				(u_char)p[3]
			);
		printf("%-16s ", s_ip);

		p = (char*)&ip_hdr->daddr;
		sprintf(s_ip, "%d.%d.%d.%d ",
				(u_char)p[0],
				(u_char)p[1],
				(u_char)p[2],
				(u_char)p[3]
			);
		printf("%-16s ", s_ip);

		switch(ip_hdr->protocol) {
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

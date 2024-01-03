#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
	struct ifreq ifr;
	struct ifconf ifc;
	struct sockaddr_in *addr;
	char buf[2048];
	char *address;
	int count = 0;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		printf("socket error\n");
		return -1;
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
		printf("ioctl error\n");
		return -1;
	}

	struct ifreq *it = ifc.ifc_req;
	const struct ifreq *const end =
	    it + (ifc.ifc_len / sizeof(struct ifreq));
	for (; it != end; ++it) {
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) != 0) {
			printf("get mac info error\n");
			continue;
		}
		if (ifr.ifr_flags & IFF_LOOPBACK)
			continue;

		if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
			unsigned char *ptr;
			char str_macaddr[64];

			count++;
			ptr =
			    (unsigned char *)&ifr.ifr_ifru.ifru_hwaddr.
			    sa_data[0];

			snprintf(str_macaddr, 64,
				 "%02X:%02X:%02X:%02X:%02X:%02X", *(ptr + 0),
				 *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4),
				 *(ptr + 5));
			printf("%d. %-16s \n", count, ifr.ifr_name);
			printf("\tmac %-16s\n", str_macaddr);
		}

		if (ioctl(sock, SIOCGIFADDR, &ifr) == 0) {
			addr = (struct sockaddr_in *)&(ifr.ifr_addr);
			address = inet_ntoa(addr->sin_addr);
			printf("\tinet %s\n", address);
		}

		if (ioctl(sock, SIOCGIFNETMASK, &ifr) == 0) {
			addr = (struct sockaddr_in *)&(ifr.ifr_addr);
			address = inet_ntoa(addr->sin_addr);
			printf("\tmask %s\n", address);
		}

		if (ioctl(sock, SIOCGIFBRDADDR, &ifr) == 0) {
			addr = (struct sockaddr_in *)&(ifr.ifr_addr);
			address = inet_ntoa(addr->sin_addr);
			printf("\tbroad %s\n", address);
		}
	}

	close(sock);

	return 0;
}

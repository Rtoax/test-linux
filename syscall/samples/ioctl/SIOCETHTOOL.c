#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <net/if.h>

#include <linux/sockios.h>
#include <linux/ethtool.h>


int main(int argc, char* argv[])
{
	int fd;
	int ret;
	unsigned int n_stats;
	struct ethtool_value edata;
	struct ifreq ifr;
	struct {
		struct ethtool_sset_info hdr;
		unsigned int buf[1];
	} sset_info;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	sset_info.hdr.cmd = ETHTOOL_GSSET_INFO;
	sset_info.hdr.reserved = 0;
	sset_info.hdr.sset_mask = 1ULL << ETH_SS_STATS;

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, "eno1");

	/* ETHTOOL_GSSET_INFO */
	ifr.ifr_data = (void*)&sset_info;

	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (0 != ret) {
		printf("errno=%d\n", errno);
		return -1;
	}

	n_stats = sset_info.hdr.sset_mask ? sset_info.hdr.data[0] : 0;
	printf("stats count = %d\n", n_stats);

	/* ETHTOOL_GLINK */
	edata.cmd = ETHTOOL_GLINK;
	ifr.ifr_data = (caddr_t)&edata;

	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (0 != ret) {
		printf("errno=%d\n", errno);
		return -1;
	}

	if (edata.data) {
		printf("Link detected on %s\n", ifr.ifr_name);
	}

	return 0;
}

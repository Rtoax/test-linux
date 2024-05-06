#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#include <linux/ethtool.h>
#include <linux/sockios.h>


static void usage(void)
{
	printf("usage: ipconfig [interface]\n");
	exit(1);
}

int detect_mii(int skfd, char *ifname)
{
	struct ifreq ifr;
	u16 *data, mii_val;
	unsigned __attribute__((unused)) phy_id;

	/*get the vitals from the interface*/
	strncpy(ifr.ifr_name, ifname, strlen(ifname)+1);

	if (ioctl(skfd, SIOCGMIIPHY, &ifr) < 0) {
		printf("SIOCGMIIPHY on %s failed\n", ifname);
		(void )close(skfd);
		return 2;
	}

	data = (u16*)(&ifr.ifr_data);
	phy_id = data[0];
	data[1] = 1;

	if (ioctl(skfd, SIOCGMIIREG, &ifr) < 0) {
		printf("SIOCGMIIREG on %s failed\n", ifname);
		//(void )close(skfd);
		return 2;
	}

	mii_val = data[3];

	return (((mii_val & 0x0016) == 0x0004) ? 0 : 1);
}

int detect_ethtool(int skfd, char *ifname)
{
	struct ifreq ifr;
	struct ethtool_value edata;

	memset(&ifr, 0, sizeof(ifr));

	edata.cmd = ETHTOOL_GLINK;

	strncpy(ifr.ifr_name, ifname, strlen(ifname)+1);
	ifr.ifr_data = (char*)&edata;

	if (ioctl(skfd, SIOCETHTOOL, &ifr) < 0) {
		printf("SIOCETHTOOL failed: %m\n");
		return 2;
	}

	return edata.data ? 0 : 1;
}

int main(int argc, char *argv[])
{
	int skfd = -1;
	char *ifname;

	int retval;

	if (argv[1]) {
		ifname = argv[1];
	} else {
		usage();
		exit(0);
	}

	/*open a socket*/
	skfd = socket(AF_INET, SOCK_DGRAM, 0);

	retval = detect_ethtool(skfd, ifname);
	if (retval == 2) {
		retval = detect_mii(skfd, ifname);
	}
	close(skfd);

	if (retval == 2)
		printf("could not determine status\n");
	if (retval == 1)
		printf("link down\n");
	if (retval == 0)
		printf("link up\n");

	return retval;
}

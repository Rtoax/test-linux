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

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	unsigned int n_stats;
	struct ethtool_value edata;
	struct ifreq ifr;
	struct ethtool_cmd cmd;
	struct {
		struct ethtool_sset_info hdr;
		unsigned int buf[1];
	} sset_info;

	if (argc < 2) {
		fprintf(stderr, "%s [ifname]\n", argv[0]);
		exit(1);
	}

	const char *ifname = argv[1];

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	sset_info.hdr.cmd = ETHTOOL_GSSET_INFO;
	sset_info.hdr.reserved = 0;
	sset_info.hdr.sset_mask = 1ULL << ETH_SS_STATS;

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, ifname);

	/* ETHTOOL_GSSET_INFO */
	ifr.ifr_data = (void *)&sset_info;

	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (ret) {
		printf("ioctl %m\n");
		return -1;
	}

	n_stats = sset_info.hdr.sset_mask ? sset_info.hdr.data[0] : 0;
	printf("stats count = %d\n", n_stats);

	/* ETHTOOL_GLINK */
	edata.cmd = ETHTOOL_GLINK;
	ifr.ifr_data = (caddr_t)&edata;

	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (ret) {
		printf("ioctl %m\n");
		return -1;
	}

	if (edata.data) {
		printf("Link detected on %s\n", ifr.ifr_name);
	}

	struct ethtool_channels channels = { .cmd = ETHTOOL_GCHANNELS };
	memset(&ifr, 0x00, sizeof(ifr));
	ifr.ifr_data = (void *)&channels;
	memcpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (ret) {
		printf("ioctl %m\n");
		return -1;
	}
	printf("Channel: max rx %d, max tx %d\n", channels.max_rx, channels.max_tx);
	printf("Channel: rx count %d, tx count %d\n", channels.rx_count, channels.tx_count);

	/* ETHTOOL_GSET */
	cmd.cmd = ETHTOOL_GSET;
	ifr.ifr_data = (caddr_t)&cmd;
	ret = ioctl(fd, SIOCETHTOOL, &ifr);
	if (ret) {
		printf("ioctl %m\n");
		return -1;
	}
	printf("supported           %d \n", cmd.supported);
	printf("advertising         %d \n", cmd.advertising);
	printf("speed               %d Mb \n", cmd.speed);
	printf("duplex              %u \n", cmd.duplex);
	printf("port                %u \n", cmd.port);
	printf("phy_address         %u \n", cmd.phy_address);
	printf("transceiver         %u \n", cmd.transceiver);
	printf("autoneg             %u \n", cmd.autoneg);
	printf("mdio_support        %u \n", cmd.mdio_support);
	printf("maxtxpkt            %d \n", cmd.maxtxpkt);
	printf("maxrxpkt            %d \n", cmd.maxrxpkt);
	printf("speed_hi            %d \n", cmd.speed_hi);
	printf("eth_tp_mdix         %u \n", cmd.eth_tp_mdix);
	printf("eth_tp_mdix_ctrl    %u \n", cmd.eth_tp_mdix_ctrl);
	printf("lp_advertising      %d \n", cmd.lp_advertising);

	return 0;
}

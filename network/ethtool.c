#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <endian.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <net/if.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/ethtool.h>

#ifndef SIOCETHTOOL
#define SIOCETHTOOL 0x8946
#endif

#define u64 __u64
#define u32 __u32

#ifndef offsetof
#define offsetof(type, number) __builtin_offsetof(type, number)
#endif


/* Context for sub-commands */
struct cmd_context {
	const char *devname;	/* net device name */
	int fd;			/* socket suitable for ethtool ioctl */
	struct ifreq ifr;	/* ifreq suitable for ethtool ioctl */
	unsigned int argc;	/* number of arguments to the sub-command */
	char **argp;		/* arguments to the sub-command */
	unsigned long debug;	/* debugging mask */
	bool json;		/* Output JSON, if supported */
#ifdef ETHTOOL_ENABLE_NETLINK
	struct nl_context *nlctx;	/* netlink context (opaque) */
#endif
};

int send_ioctl(struct cmd_context *ctx, void *cmd)
{
	ctx->ifr.ifr_data = cmd;
	return ioctl(ctx->fd, SIOCETHTOOL, &ctx->ifr);
}

static int dump_drvinfo(struct ethtool_drvinfo *info)
{
	fprintf(stdout,
		"driver: %.*s\n"
		"version: %.*s\n"
		"firmware-version: %.*s\n"
		"expansion-rom-version: %.*s\n"
		"bus-info: %.*s\n"
		"supports-statistics: %s\n"
		"supports-test: %s\n"
		"supports-eeprom-access: %s\n"
		"supports-register-dump: %s\n"
		"supports-priv-flags: %s\n",
		(int)sizeof(info->driver), info->driver,
		(int)sizeof(info->version), info->version,
		(int)sizeof(info->fw_version), info->fw_version,
		(int)sizeof(info->erom_version), info->erom_version,
		(int)sizeof(info->bus_info), info->bus_info,
		info->n_stats ? "yes" : "no",
		info->testinfo_len ? "yes" : "no",
		info->eedump_len ? "yes" : "no",
		info->regdump_len ? "yes" : "no",
		info->n_priv_flags ? "yes" : "no");

	return 0;
}

static void exit_bad_args(void) __attribute__((noreturn));

static void exit_bad_args(void)
{
	fprintf(stderr,
		"ethtool: bad command line argument(s)\n"
		"For more information run ethtool -h\n");
	exit(1);
}

static int do_gdrv(struct cmd_context *ctx)
{
	int err;
	struct ethtool_drvinfo drvinfo;

	if (ctx->argc != 0)
		exit_bad_args();

	drvinfo.cmd = ETHTOOL_GDRVINFO;
	err = send_ioctl(ctx, &drvinfo);
	if (err < 0) {
		perror("Cannot get driver information");
		return 71;
	}
	return dump_drvinfo(&drvinfo);
}

static long long
get_int_range(char *str, int base, long long min, long long max)
{
	long long v;
	char *endp;

	if (!str)
		exit_bad_args();
	errno = 0;
	v = strtoll(str, &endp, base);
	if (errno || *endp || v < min || v > max)
		exit_bad_args();
	return v;
}

unsigned long long
get_uint_range(char *str, int base, unsigned long long max)
{
	unsigned long long v;
	char *endp;

	if (!str)
		exit_bad_args();
	errno = 0;
	v = strtoull(str, &endp, base);
	if (errno || *endp || v > max)
		exit_bad_args();
	return v;
}

static int get_int(char *str, int base)
{
	return get_int_range(str, base, INT_MIN, INT_MAX);
}

static int do_phys_id(struct cmd_context *ctx)
{
	int err;
	struct ethtool_value edata;
	int phys_id_time;

	if (ctx->argc > 1)
		exit_bad_args();
	if (ctx->argc == 1)
		phys_id_time = get_int(*ctx->argp, 0);
	else
		phys_id_time = 0;

	edata.cmd = ETHTOOL_PHYS_ID;
	edata.data = phys_id_time;
	err = send_ioctl(ctx, &edata);
	if (err < 0)
		perror("Cannot identify NIC");

	return err;
}

static int ioctl_init(struct cmd_context *ctx, bool no_dev)
{
	if (no_dev) {
		ctx->fd = -1;
		return 0;
	}
	if (strlen(ctx->devname) >= IFNAMSIZ) {
		fprintf(stderr, "Device name longer than %u characters\n",
			IFNAMSIZ - 1);
		exit_bad_args();
	}

	/* Setup our control structures. */
	memset(&ctx->ifr, 0, sizeof(ctx->ifr));
	strcpy(ctx->ifr.ifr_name, ctx->devname);

	/* Open control socket. */
	ctx->fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (ctx->fd < 0)
		ctx->fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	if (ctx->fd < 0) {
		perror("Cannot get control socket");
		return 70;
	}

	return 0;
}

static struct ethtool_gstrings *
get_stringset(struct cmd_context *ctx, enum ethtool_stringset set_id,
		ptrdiff_t drvinfo_offset, int null_terminate)
{
	struct {
		struct ethtool_sset_info hdr;
		u32 buf[1];
	} sset_info;
	struct ethtool_drvinfo drvinfo;
	u32 len, i;
	struct ethtool_gstrings *strings;

	sset_info.hdr.cmd = ETHTOOL_GSSET_INFO;
	sset_info.hdr.reserved = 0;
	sset_info.hdr.sset_mask = 1ULL << set_id;

	if (send_ioctl(ctx, &sset_info) == 0) {
		const u32 *sset_lengths = sset_info.hdr.data;

		len = sset_info.hdr.sset_mask ? sset_lengths[0] : 0;
	} else if (errno == EOPNOTSUPP && drvinfo_offset != 0) {
		/* Fallback for old kernel versions */
		drvinfo.cmd = ETHTOOL_GDRVINFO;
		if (send_ioctl(ctx, &drvinfo))
			return NULL;
		len = *(u32 *)((char *)&drvinfo + drvinfo_offset);
	} else {
		return NULL;
	}

	strings = calloc(1, sizeof(*strings) + len * ETH_GSTRING_LEN);
	if (!strings)
		return NULL;

	strings->cmd = ETHTOOL_GSTRINGS;
	strings->string_set = set_id;
	strings->len = len;
	if (len != 0 && send_ioctl(ctx, strings)) {
		free(strings);
		return NULL;
	}

	if (null_terminate)
		for (i = 0; i < len; i++)
			strings->data[(i + 1) * ETH_GSTRING_LEN - 1] = 0;

	return strings;
}

static int dump_test(struct ethtool_test *test, struct ethtool_gstrings *strings)
{
	unsigned int i;
	int rc;

	rc = test->flags & ETH_TEST_FL_FAILED;
	fprintf(stdout, "The test result is %s\n", rc ? "FAIL" : "PASS");

	if (test->flags & ETH_TEST_FL_EXTERNAL_LB)
		fprintf(stdout, "External loopback test was %sexecuted\n",
			(test->flags & ETH_TEST_FL_EXTERNAL_LB_DONE) ? "" : "not ");

	if (strings->len)
		fprintf(stdout, "The test extra info:\n");

	for (i = 0; i < strings->len; i++) {
		fprintf(stdout, "%s\t %d\n", (char *)(strings->data + i * ETH_GSTRING_LEN),
			(u32) test->data[i]);
	}

	fprintf(stdout, "\n");
	return rc;
}

static int do_test(struct cmd_context *ctx)
{
	enum {
		ONLINE = 0,
		OFFLINE,
		EXTERNAL_LB,
	} test_type;
	int err;
	struct ethtool_test *test;
	struct ethtool_gstrings *strings;

	if (ctx->argc > 1)
		exit_bad_args();
	if (ctx->argc == 1) {
		if (!strcmp(ctx->argp[0], "online"))
			test_type = ONLINE;
		else if (!strcmp(*ctx->argp, "offline"))
			test_type = OFFLINE;
		else if (!strcmp(*ctx->argp, "external_lb"))
			test_type = EXTERNAL_LB;
		else
			exit_bad_args();
	} else {
		test_type = OFFLINE;
	}

	strings = get_stringset(ctx, ETH_SS_TEST,
				offsetof(struct ethtool_drvinfo, testinfo_len),
				1);
	if (!strings) {
		perror("Cannot get strings");
		return 74;
	}

	test = calloc(1, sizeof(*test) + strings->len * sizeof(u64));
	if (!test) {
		perror("Cannot allocate memory for test info");
		free(strings);
		return 73;
	}
	memset(test->data, 0, strings->len * sizeof(u64));
	test->cmd = ETHTOOL_TEST;
	test->len = strings->len;
	if (test_type == EXTERNAL_LB)
		test->flags = (ETH_TEST_FL_OFFLINE | ETH_TEST_FL_EXTERNAL_LB);
	else if (test_type == OFFLINE)
		test->flags = ETH_TEST_FL_OFFLINE;
	else
		test->flags = 0;
	err = send_ioctl(ctx, test);
	if (err < 0) {
		perror("Cannot test");
		free(test);
		free(strings);
		return 74;
	}

	err = dump_test(test, strings);
	free(test);
	free(strings);

	return err;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage:%s [devname].\n", argv[0]);
		exit(0);
	}

	struct cmd_context ctx;
	ctx.devname = argv[1];

	ioctl_init(&ctx, 0);
	do_gdrv(&ctx);
	do_phys_id(&ctx);
	do_test(&ctx);

	return 0;
}

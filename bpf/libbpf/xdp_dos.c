#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <linux/if_xdp.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <malloc.h>
#include <net/if.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "trace_helpers.h"
#include "libbpf_wrapper.h"
#include "libxdp_helpers.h"

#include "xdp_dos.skel.h"
#include "xdp_dos.h"

#define NAME xdp_dos
#include "skel_defs.h"


static int ifindex = -1;
static const char *ifname;

/**
 * User space configuration, pass to xdp program with map.
 */
static const int key_user_config = MAP_KEY_USER_CONFIG;
static struct user_config config = {
	.sample_secs = -1,
	.sample_threshold = -1,
	.blacklist_sample_secs = -1,
	.blacklist_sample_threshold = -1,
};

static int ipv4_white_count = 0;
static struct ipv4_addr_t *ipv4_white_list = NULL;

/**
 * Use to IPRandom
 */
static int ipv4_IPrandom_count = 0;
static struct ipv4_addr_t *ipv4_IPrandom_list = NULL;

static __u64 drop_pkt_count = 0;

static int verbose = 0;

/**
 * Logs
 */
static FILE *packet_filter_fp = NULL;
static FILE *packet_mutate_fp = NULL;

static const char argp_prog_doc[] =
	"USAGE: [-i <ifname>] [-W <address>] [-v] ...\n";

static const struct argp_option opts[] = {
	{ "ifname", 'i', "INTERFACE", 0, "Network ifname to attach" },
	{ "sample-secs", 't', "SAMPLE_SECS", 0, "Sample interval" },
	{ "sample-threshold", 'n', "SAMPLE_THRESHOLD", 0, "Sample threshold, MAX" },
	{ "blacklist-sample-secs", 'T', "BLACKLIST_SAMPLE_SECS", 0, "Blacklist sample interval" },
	{ "blacklist-sample-threshold", 'N', "BLACKLIST_SAMPLE_THRESHOLD", 0, "Blacklist sample threshold" },
	{ "white", 'W', "WHITE", 0, "Add address to white list" },
	{ "rand", 'R', "RAND", 0, "Use to IPRandom" },
	{ "verbose", 'v', NULL, 1, "Display the detail, for debug maybe" },
	{},
};

static void add_white(const char *p)
{
	int err;
	struct sockaddr_in addr;

	err = inet_pton(AF_INET, p, &addr.sin_addr);
	if (err < 0) {
		fprintf(stderr, "Bad address %s\n", p);
		abort();
	}

	if (verbose)
		fprintf(stderr, "Add address %s(0x%x) to whitelist.\n", p,
			addr.sin_addr.s_addr);

	ipv4_white_list = realloc(ipv4_white_list, ++ipv4_white_count);

	ipv4_white_list[ipv4_white_count - 1].addr = addr.sin_addr.s_addr;
}

static void add_rand(const char *p)
{
	int err;
	struct sockaddr_in addr;

	err = inet_pton(AF_INET, p, &addr.sin_addr);
	if (err < 0) {
		fprintf(stderr, "Bad address %s\n", p);
		abort();
	}

	if (verbose)
		fprintf(stderr, "Add address %s(0x%x) to IPRandom list.\n", p,
			addr.sin_addr.s_addr);

	ipv4_IPrandom_list = realloc(ipv4_IPrandom_list, ++ipv4_IPrandom_count);

	ipv4_IPrandom_list[ipv4_IPrandom_count - 1].addr = addr.sin_addr.s_addr;
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		ifname = arg;
		ifindex = if_nametoindex(ifname);
		if (!ifindex)
			ifindex = atoi(ifname);
		break;
	case 't':
		config.sample_secs = atoi(arg);
		break;
	case 'n':
		config.sample_threshold = atoi(arg);
		break;
	case 'T':
		config.blacklist_sample_secs = atoi(arg);
		break;
	case 'N':
		config.blacklist_sample_threshold = atoi(arg);
		break;
	case 'W':
		add_white(arg);
		break;
	case 'R':
		add_rand(arg);
		break;
	case 'v':
		verbose = 1;
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

static void sig_handler(int sig)
{
	if (verbose)
		read_trace_pipe_stop();
}

static const char *strevtaction(int action)
{
#define BLACK	"\033[1;31m"
#define WHITE	"\033[1;37m"
#define RST	"\033[m"
	switch (action) {
	case AC_NONE: return "AC_NONE";
	case AC_NEW_IP_ADDR: return "AC_NEW_IP_ADDR";
	case AC_MOVE_TO_BLACKLIST: return BLACK"AC_MOVE_TO_BLACKLIST"RST;
	case AC_STAT_IN_BLACKLIST: return BLACK"AC_STAT_IN_BLACKLIST"RST;
	case AC_REMOVE_FROM_BLACKLIST: return WHITE"AC_REMOVE_FROM_BLACKLIST"RST;
	case AC_STAT_IN_WHITELIST: return WHITE"AC_STAT_IN_WHITELIST"RST;
	default: return "?";
	}
#undef BLACK
#undef WHITE
#undef RST
}
void dump_data_to_file(const char *filename, char *data, size_t data_len)
{
	FILE *fp = fopen(filename, "w");

	fprintf(stdout, "Dump droped packet (len = %ld) to %s\n", data_len,
		filename);

	fwrite(data, 1, data_len, fp);

	fclose(fp);
}

void handle_event(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct event_t *e = data;
	char time_buf[128];
	struct timeval tv;
	char buf[128], *ifname;
	char saddr_buf[64];
	struct in_addr in = { .s_addr = e->saddr, };

	snprintf(saddr_buf, 64, "%s", inet_ntoa(in));

	gettimeofday(&tv, NULL);
	strftime(time_buf, 128, "%Y年%m月%d日", localtime(&tv.tv_sec));

	ifname = if_indextoname(e->rx_ifindex, buf);

	if (e->action == AC_MOVE_TO_BLACKLIST) {
		fprintf(packet_filter_fp, "%s，检测到来自 %s 地址拒绝服务攻击\n",
			time_buf, saddr_buf);
		fprintf(packet_filter_fp, "%s，添加 %s 地址到黑名单\n",
			time_buf, saddr_buf);
	} else if (e->action == AC_STAT_IN_BLACKLIST) {
		/**
		 * Only ICMP here, no need to parse e->protocol, just Display
		 * "ICMP".
		 */
		if (e->black_action == AC_BLACK_PASS)
			fprintf(packet_filter_fp, "%s，来自 %s 地址的 %s 协议数据包被放行，优先级%d\n",
				time_buf, saddr_buf, "ICMP", e->icmp_prio);
		else if (e->black_action == AC_BLACK_DROP) {
			fprintf(packet_filter_fp, "%s，来自 %s 地址的 %s 协议数据包被丢弃，优先级%d\n",
				time_buf, saddr_buf, "ICMP", e->icmp_prio);

			if (e->random_saddr) {
				char rand_saddr_buf[64];
				struct in_addr in_rand = { .s_addr = e->random_saddr, };
				snprintf(rand_saddr_buf, 64, "%s", inet_ntoa(in_rand));
				fprintf(packet_mutate_fp, "%s，来自 %s 地址的 %s 协议被 IPRandom 修改源地址为 %s\n",
					time_buf, saddr_buf, "ICMP", rand_saddr_buf);
			}

			/* Dump droped packet to file */
			char filename[512], time_buf2[128];
			struct timeval tv2;

			gettimeofday(&tv2, NULL);
			strftime(time_buf2, 128, "%Y年%m月%d日-%H时%M分%S秒", localtime(&tv2.tv_sec));
			snprintf(filename, 512, "%s/%s-%s-%lld.ca",
				DIR_FILTER_DUMP, time_buf2, saddr_buf, ++drop_pkt_count);

			dump_data_to_file(filename, e->pkt_data, e->pkt_len);
		}
	} else if (e->action == AC_REMOVE_FROM_BLACKLIST) {
		fprintf(packet_filter_fp, "%s，将 %s 地址从黑名单移除\n",
			time_buf, saddr_buf);
	}

	printf("%s : %-10s %-16s %-16s\n", time_buf, ifname,
		strxdpaction(e->xdp_action), strevtaction(e->action));
}

void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
	printf("lost event\n");
}

int main(int argc, char *argv[])
{
	int err, i, prog_fd;
	int white_map_fd, rand_map_fd, config_map_fd, events_fd;
	struct struct_bpf *skel;
	struct perf_buffer *perf_buf = NULL;
	int xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify ifname with -i\n");
		return -EINVAL;
	}

	if (config.sample_secs == -1) {
		fprintf(stderr, "Must specify sample interval seconds with -t\n");
		exit(EXIT_FAILURE);
	}

	if (config.sample_threshold == -1) {
		fprintf(stderr, "Must specify sample threshold seconds with -n\n");
		exit(EXIT_FAILURE);
	}

	if (config.blacklist_sample_secs == -1) {
		fprintf(stderr, "Must specify blacklist sample interval seconds with -T\n");
		exit(EXIT_FAILURE);
	}

	if (config.blacklist_sample_threshold == -1) {
		fprintf(stderr, "Must specify sample threshold seconds with -N\n");
		exit(EXIT_FAILURE);
	}

	printf("Config sampling interval %d seconds\n", config.sample_secs);
	printf("Config sampling threshold %d packets\n", config.sample_threshold);
	printf("Config blacklist recover sampling interval %d seconds\n", config.blacklist_sample_secs);
	printf("Config blacklist recover sampling threshold %d packets\n", config.blacklist_sample_threshold);

	/**
	 * Open all logs
	 */
	packet_filter_fp = fopen(LOG_PACKET_FILTER, "w");
	if (!packet_filter_fp) {
		fprintf(stderr, "open log %s failed.\n", LOG_PACKET_FILTER);
		exit(EXIT_FAILURE);
	}

	packet_mutate_fp = fopen(LOG_PACKET_MUTATE, "w");
	if (!packet_mutate_fp) {
		fprintf(stderr, "open log %s failed.\n", LOG_PACKET_MUTATE);
		exit(EXIT_FAILURE);
	}

	/* Create filter dump capture directory if not exist */
	system("rm -f " DIR_FILTER_DUMP "/*");
	mkdir(DIR_FILTER_DUMP, 0777);

	skel = BPF__OPEN_AND_LOAD(_bpf__open_and_load, _bpf__open_opts,
			_bpf__load, _bpf__destroy);

	bpf_program__set_type(skel->progs.xdp_dummy_prog, BPF_PROG_TYPE_XDP);

	prog_fd = bpf_program__fd(skel->progs.xdp_dummy_prog);
	config_map_fd = bpf_map__fd(skel->maps.map_config);
	white_map_fd = bpf_map__fd(skel->maps.map_whitelist);
	rand_map_fd = bpf_map__fd(skel->maps.map_iprandom);

	for (i = 0; i < ipv4_white_count; i++) {
		int key = ipv4_white_list[i].addr;
		err = bpf_map_update_elem(white_map_fd, &key, &ipv4_white_list[i], 0);
		if (err < 0) {
			printf("failed to update whitelist elem.\n");
			goto cleanup;
		}
	}

	for (i = 0; i < ipv4_IPrandom_count; i++) {
		int key = ipv4_IPrandom_list[i].addr;
		err = bpf_map_update_elem(rand_map_fd, &key, &ipv4_IPrandom_list[i], 0);
		if (err < 0) {
			printf("failed to update IPrandom list elem.\n");
			goto cleanup;
		}
	}

	err = bpf_map_update_elem(config_map_fd, &key_user_config, &config, 0);
	if (err < 0) {
		printf("failed to update user config elem.\n");
		goto cleanup;
	}

	events_fd = bpf_map__fd(skel->maps.events);

	perf_buf = libbpf_perf_buffer__new(events_fd, 1024, handle_event, lost_event);
	if (!perf_buf) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}

	err = libbpf_bpf_xdp_attach(ifindex, prog_fd, xdp_flags);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

	if (verbose)
		read_trace_pipe_start();

	while (true) {
		err = perf_buffer__poll(perf_buf, 100 /* timeout, ms */);
		/* Ctrl-C gives -EINTR */
		if (err == -EINTR) {
			err = 0;
			break;
		}
		if (err < 0) {
			printf("Error polling perf buffer: %d\n", err);
			break;
		}
	}

cleanup:
	if (verbose)
		read_trace_pipe_wait();
	printf("Detach xdp from ifname %s\n", ifname);
	libbpf_bpf_xdp_detach(ifindex, xdp_flags);
	_bpf__destroy(skel);
	fclose(packet_filter_fp);
	fclose(packet_mutate_fp);
	return 0;
}

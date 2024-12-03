#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/resource.h>
#include <getopt.h>
#include <net/if.h>
#include <time.h>

#include <arpa/inet.h>
#include <linux/if_link.h>

#include <bpf/bpf.h>
#include <bpf/libbpf.h>

#define XDP_ACTION_MAX_STRLEN 11

static int ifindex = -1;
static char ifname_buf[IF_NAMESIZE];
static char *ifname;
static __u32 prog_id;

static __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

struct config {
	__u32 action;
	int ifindex;
	__u32 options;
};

static const struct option long_options[] = {
	{"help",	no_argument,		NULL, 'h' },
	{"dev",		required_argument,	NULL, 'd' },
	{"action",	required_argument,	NULL, 'a' },
	{"force",	no_argument,		NULL, 'F' },
	{0, 0, NULL,  0 }
};

static void usage(char *argv[])
{
	int i;

	printf("\n");
}


int main(int argc, char **argv)
{
	int opt, err, longindex = 0;
	char action_str_buf[XDP_ACTION_MAX_STRLEN + 1 /* for \0 */] = { 0 };
	int action = XDP_PASS; /* Default action */
	char *action_str = NULL;
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	struct bpf_object *obj;
	int prog_fd, config_map_fd;
	char filename[256];
	struct bpf_map *config_map;
	struct config cfg = { 0 };
	__u32 key = 0;
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);


	snprintf(filename, sizeof(filename), "%s.kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return -1;

	config_map =  bpf_object__find_map_by_name(obj, "config_map");
	if (!config_map) {
		printf("finding a config_map in obj file failed\n");
		return -1;
	}

	config_map_fd = bpf_map__fd(config_map);

	/* Parse commands line args */
	while ((opt = getopt_long(argc, argv, "Fhd:a:",
				  long_options, &longindex)) != -1) {
		switch (opt) {
		case 'd':
			if (strlen(optarg) >= IF_NAMESIZE) {
				fprintf(stderr, "ERR: --dev name too long\n");
				goto error;
			}
			ifname = (char *)&ifname_buf;
			strncpy(ifname, optarg, IF_NAMESIZE);
			ifindex = if_nametoindex(ifname);
			if (ifindex == 0) {
				fprintf(stderr,
					"ERR: --dev name unknown err(%d):%s\n",
					errno, strerror(errno));
				goto error;
			}
			break;
		case 'a':
			action_str = (char *)&action_str_buf;
			strncpy(action_str, optarg, XDP_ACTION_MAX_STRLEN);
			break;
		case 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			break;
		case 'h':
		error:
		default:
			usage(argv);
			return EINVAL;
		}
	}

	cfg.ifindex = ifindex;
	cfg.action = action;

	/* User-side setup ifindex in config_map */
	err = bpf_map_update_elem(config_map_fd, &key, &cfg, 0);
	if (err) {
		fprintf(stderr, "Store config failed (err:%d)\n", err);
		exit(1);
	}

	if (bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags) < 0) {
		fprintf(stderr, "link set xdp fd failed\n");
		return -1;
	}

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	if (err) {
		printf("can't get prog info - %s\n", strerror(errno));
		return err;
	}
	prog_id = info.id;

	return 0;
}

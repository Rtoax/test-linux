// SPDX-License-Identifier: GPL-3.0
#include <argp.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "cgroup_sysctl.skel.h"
#include "trace_helpers.h"

const char *cgroup_path;

const char argp_prog_doc[] =
	"USAGE: [-c <cgroupv2 path>]\n"
	"\n"
	"	# create cgroupv2\n"
	"	sudo mkdir a.mnt\n"
	"	sudo mount -t cgroupv2 none a.mnt\n"
	"	sudo mkdir a.mnt/foo\n"
	"	\n"
	"	# run script\n"
	"	sudo ./cgroup_sysctl -c a.mnt/foo\n"
	"	\n"
	"	# start a new bash, attach pid to cgroup foo, and run test\n"
	"	echo $$ | sudo tee .../a.mnt/foo/cgroup.procs\n"
	"	sysctl -a\n"
	"\n";

static const struct argp_option opts[] = {
	{ "cgroup", 'c', "CGROUP", 0, "Cgroup v2 to attach" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'c':
		cgroup_path = arg;
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

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	return vfprintf(stderr, format, args);
}

static void sig_int(int signo)
{
	read_trace_pipe_stop();
}

int main(int argc, char **argv)
{
	struct cgroup_sysctl_bpf *skel;
	int err;
	int cgroup_fd, prog_fd;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (!cgroup_path) {
		fprintf(stderr, "Specify cgroup path with -c\n");
		return -EINVAL;
	}

	libbpf_set_print(libbpf_print_fn);

	if (signal(SIGINT, sig_int) == SIG_ERR) {
		fprintf(stderr, "can't set signal handler: %m\n");
		return 1;
	}

	skel = cgroup_sysctl_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n");
		return 1;
	}

	err = cgroup_sysctl_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	cgroup_fd = open(cgroup_path, O_RDONLY);
	if (cgroup_fd == -1) {
		fprintf(stderr, "Open cgroup failed: %m.\n");
		goto cleanup;
	}

	prog_fd = bpf_program__fd(skel->progs.sysctl_printk_display);
	err = bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_SYSCTL, 0);
	if (err) {
		fprintf(stderr, "Attach cgroup to prog failed: %m.\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	bpf_prog_detach(cgroup_fd, BPF_CGROUP_SYSCTL);
	cgroup_sysctl_bpf__destroy(skel);
	close(cgroup_fd);
	return -err;
}

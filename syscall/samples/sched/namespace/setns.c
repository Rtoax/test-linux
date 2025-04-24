#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <argp.h>
#include <sched.h>
#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

pid_t target_pid = -1;
static char *ns_str = "pid";
static int nstype = CLONE_NEWPID;
int verbose = 0;

struct extra_args {
	int argc;
	char **argv;
};

const char argp_prog_doc[] =
	"USAGE: [-p <pid>] [-n <ns>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "pid", 'p', "PID", 0, "specify target pid, use to locate /proc/PID" },
	{ "ns", 'n', "NAMESPACE", 0, "specify namespace, use to locate /proc/PID/ns/<ns>" },
	{ "verbose", 'v', NULL, 1, "display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	struct extra_args *extra_args = state->input;

	switch (key) {
	case 'p':
		target_pid = atoi(arg);
		break;
	case 'n':
		ns_str = arg;
		if (!strcmp(ns_str, "cgroup"))
			nstype = CLONE_NEWCGROUP;
		else if (!strcmp(ns_str, "ipc"))
			nstype = CLONE_NEWIPC;
		else if (!strcmp(ns_str, "mnt"))
			nstype = CLONE_NEWNS;
		else if (!strcmp(ns_str, "net"))
			nstype = CLONE_NEWNET;
		else if (!strcmp(ns_str, "pid"))
			nstype = CLONE_NEWPID;
#ifdef CLONE_NEWTIME
		else if (!strcmp(ns_str, "time"))
			nstype = CLONE_NEWTIME;
#endif
		else if (!strcmp(ns_str, "user"))
			nstype = CLONE_NEWUSER;
		else if (!strcmp(ns_str, "uts"))
			nstype = CLONE_NEWUTS;
		else {
			fprintf(stderr, "ERROR: nstype only support cgroup,ipc,mnt,net,pid,"
#ifdef CLONE_NEWTIME
				"time,"
#endif
				"user,uts\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		extra_args->argv = realloc(extra_args->argv, (extra_args->argc + 1) * sizeof(char *));
		extra_args->argv[extra_args->argc++] = arg;
		break;
	case ARGP_KEY_END:
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


int sys_setns(int fd, int nstype)
{
	return syscall(SYS_setns, fd, nstype);
}

int main(int argc, char *argv[])
{
	int i, fd, err;
	char buf[128] = "/proc/999999999/ns/cgroup";
	struct extra_args extra_args = {0};


	err = argp_parse(&argp, argc, argv, 0, NULL, &extra_args);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (target_pid == -1) {
		fprintf(stderr, "ERROR: Need -p PID.\n");
		exit(EXIT_FAILURE);
	}

	snprintf(buf, sizeof(buf) - 1, "/proc/%d/ns/%s", target_pid, ns_str);

	printf("INFO: attach pid %d to %s\n", target_pid, buf);

	fd = open(buf, O_RDONLY);
	if (fd == -1){
		printf("open(%s) %m\n", buf);
		exit(1);
	}

	if (setns(fd, nstype) == -1){
		fprintf(stderr, "setns: %m\n");
		close(fd);
		exit(1);
	}
	close(fd);

	printf("EXEC: ");
	for (i = 0; i < extra_args.argc; i++) {
		printf("%s ", extra_args.argv[i]);
	}
	printf("\n");

	execvp(extra_args.argv[0], extra_args.argv);

	if (extra_args.argc > 0)
		free(extra_args.argv);

	return 0;
}

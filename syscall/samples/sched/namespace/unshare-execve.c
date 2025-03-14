/**
 * unshare(1)
 *
 * CLONE_NEWPID
 *
 * - Unshare the PID namespace, so that the calling process has a new PID
 *   namespace for its children which is not shared with any previously
 *   existing process. The calling process remains in its original namespace.
 *
 * Refs:
 * - https://github.com/util-linux/util-linux
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <err.h>
#include <sched.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static pid_t child_pid = -1;

static void usage(char *pname)
{
	fprintf(stderr, "Usage: %s [options] -- program [arg...]\n", pname);
	fprintf(stderr, "Options can be:\n");
	fprintf(stderr, "    -C   unshare cgroup namespace\n");
	fprintf(stderr, "    -i   unshare IPC namespace\n");
	fprintf(stderr, "    -m   unshare mount namespace\n");
	fprintf(stderr, "    -n   unshare network namespace\n");
	fprintf(stderr, "    -p   unshare PID namespace\n");
/* since Linux 5.6 */
#if defined(CLONE_NEWTIME)
	fprintf(stderr, "    -t   unshare time namespace\n");
#endif
	fprintf(stderr, "    -u   unshare UTS namespace\n");
	fprintf(stderr, "    -U   unshare user namespace\n");
	fprintf(stderr, "    -F   fork the specified program as a child process\n");
	exit(EXIT_FAILURE);
}

void sig_handler(int sig)
{
	psignal(sig, "Catch");
	if (child_pid != -1) {
		kill(child_pid, SIGKILL);
		waitpid(child_pid, NULL, 0);
	}
	exit(0);
}

int unshare_execv(int flags, char *argv[])
{
	printf("EXEC: %s\n", argv[0]);
	execvp(argv[0], argv);
	err(EXIT_FAILURE, "execvp");
}

int main(int argc, char *argv[])
{
	int flags, opt;
	bool flag_fork = false;

	flags = 0;

	while ((opt = getopt(argc, argv, "CimnptuUF")) != -1) {
		switch (opt) {
		case 'C': flags |= CLONE_NEWCGROUP;     break;
		case 'i': flags |= CLONE_NEWIPC;        break;
		case 'm': flags |= CLONE_NEWNS;         break;
		case 'n': flags |= CLONE_NEWNET;        break;
		case 'p': flags |= CLONE_NEWPID;        break;
/* since Linux 5.6 */
#if defined(CLONE_NEWTIME)
		case 't': flags |= CLONE_NEWTIME;       break;
#endif
		case 'u': flags |= CLONE_NEWUTS;        break;
		case 'U': flags |= CLONE_NEWUSER;       break;
		case 'F': flag_fork = true;             break;
		default:  usage(argv[0]);
		}
	}

	if (optind >= argc)
		usage(argv[0]);

	signal(SIGINT, sig_handler);

	if (unshare(flags) == -1)
		err(EXIT_FAILURE, "unshare");

	if (flag_fork) {
		child_pid = fork();
		if (child_pid == 0)
			unshare_execv(flags, &argv[optind]);
		waitpid(child_pid, NULL, 0);
	} else
		unshare_execv(flags, &argv[optind]);

	return 0;
}

/**
 * fork(2) failed with ENOMEM
 *
 * An attempt was made to create a child process in a PID namespace whose
 * "init" process has terminated. See pid_namespaces(7).
 *
 *
 *           +----> pid2 setns(pid=1)         +-----> init
 *          /                                /
 *         /                                /
 * -------*---------------o----------------*---------------------> parent
 *       fork()       unshare(pidns)   fork()
 */
#include <assert.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "fork_helpers.h"


/**
 * Save all PIDs to file, because process could see others PID.
 */
#define FILE_PID_INIT	"init.pid"
#define FILE_PID_PROC	"proc.pid"

static char *nsproc_str = "pid";
static int nstype = CLONE_NEWPID;

void parse_args(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++) {
		if (!strncmp(argv[i], "nstype=", 7)) {
			const char *ns = argv[i] + 7;
			if (!strcmp(ns, "pid")) {
				nstype = CLONE_NEWPID;
				nsproc_str = "pid";
			} else if (!strcmp(ns, "cgroup")) {
				nstype = CLONE_NEWCGROUP;
				nsproc_str = "cgroup";
			} else if (!strcmp(ns, "user")) {
				nstype = CLONE_NEWUSER;
				nsproc_str = "user";
			} else {
				fprintf(stderr, "ERROR: not support nstype %s\n", ns);
				exit(1);
			}
		} else {
			fprintf(stderr, "ERROR: unknown %s\n", argv[i]);
			exit(1);
		}
	}
}

void proc_init(void)
{
	sleep(1);
	printf("NS INIT %d.\n", getpid());
	sleep(1);
	exit(0);
}

void proc_2(void)
{
	int fd, err;
	char buf[128];
	pid_t init_pid;

	sleep(1);
	init_pid = load_pid(FILE_PID_INIT);
	printf("NS PID2 %d, INIT %d.\n", getpid(), init_pid);

	snprintf(buf, 127, "/proc/%d/ns/%s", init_pid, nsproc_str);
	fd = open(buf, O_RDONLY);
	err = setns(fd, nstype);
	if (err) {
		fprintf(stderr, "ERROR: setns %m\n");
		kill(init_pid, SIGKILL);
		abort();
	}
	close(fd);

	try_fork(0, NULL);
	try_fork(1, NULL);
	try_popen(NULL);
	try_popen("uname -a");

	sleep(2);

	/**
	 * after pid namespace init process terminated, fork will return ENOMEM.
	 */
	try_fork(0, NULL);
	try_fork(1, NULL);
	try_popen(NULL);
	try_popen("uname -a");
}

int main(int argc, char *argv[])
{
	int err;
	pid_t pid_init, pid_2;

	fprintf(stderr, "Usage: %s nstype=[pid|cgroup|user]\n", argv[0]);
	parse_args(argc - 1, &argv[1]);

	pid_2 = fork();
	if (pid_2 > 0) {
		save_pid(FILE_PID_PROC, pid_2);
		err = unshare(nstype);
		if (err) {
			perror("unshare");
			abort();
		}
		pid_init = fork();
		if (pid_init > 0)
			save_pid(FILE_PID_INIT, pid_init);
	}

	sleep(1);

	if (pid_2 == 0)
		proc_2();

	if (pid_init == 0)
		proc_init();

	if (pid_init > 0 && pid_2 > 0) {
		waitpid(pid_init, NULL, 0);
		waitpid(pid_2, NULL, 0);
	}

	return 0;
}

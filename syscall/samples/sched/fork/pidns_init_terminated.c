/**
 * fork(2) error ENOMEM
 *
 * An attempt was made to create a child process in a PID namespace whose
 * "init" process has terminated. See pid_namespaces(7).
 *
 *       _____ pid2 setns()         _____ init
 *      /                          /
 * ----+------------o-------------+--------------------->
 *    fork()      unshare()      fork()
 */
#include <assert.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FILE_PID_INIT	"pidns_init.pid"
#define FILE_PID_PROC	"pidns_proc.pid"

void try_fork(void)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		char *argv[] = {"echo", "child", NULL};
		execvp(argv[0], argv);
	}
	wait(NULL);
}

void try_popen(void)
{
	char buf[128] = "uname -rm";
	char line[256] = {0};
	FILE *fp = popen(buf, "r");
	if (fp == NULL) {
		fprintf(stderr, "popen(%s) %m\n", buf);
		return;
	}
	while (fgets(line, 256, fp))
		printf("%s\n", line);
	pclose(fp);
}

void save_pid(const char *filename, pid_t pid)
{
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: could't open %s, %m", filename);
		kill(pid, SIGKILL);
		assert(fp && "fopen()");
	}
	fprintf(fp, "%d", pid);
	fclose(fp);
}

int load_pid(const char *filename)
{
	int pid;
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "%d", &pid);
	fclose(fp);
	return pid;
}

void pidns_process_init(void)
{
	sleep(1);

	printf("NS INIT %d.\n", getpid());
	sleep(1);
	exit(0);
}

void pidns_process_2(void)
{
	int fd, err;
	char buf[128];
	pid_t init_pid;

	sleep(1);
	init_pid = load_pid(FILE_PID_INIT);
	printf("NS PID2 %d, INIT %d.\n", getpid(), init_pid);

	snprintf(buf, 127, "/proc/%d/ns/pid", init_pid);
	fd = open(buf, O_RDONLY);
	err = setns(fd, CLONE_NEWPID);
	if (err) {
		fprintf(stderr, "ERROR: setns %m\n");
		kill(init_pid, SIGKILL);
		abort();
	}
	close(fd);

	try_fork();
	try_popen();
	sleep(2);
	/**
	 * after pid namespace init process terminated, fork will return ENOMEM.
	 */
	try_fork();
	try_popen();
}

int main(int argc, char *argv[])
{
	pid_t pid_init, pid_2;

	pid_2 = fork();
	if (pid_2 > 0) {
		save_pid(FILE_PID_PROC, pid_2);
		unshare(CLONE_NEWPID);
		pid_init = fork();
		if (pid_init > 0)
			save_pid(FILE_PID_INIT, pid_init);
	}

	sleep(1);

	if (pid_2 == 0)
		pidns_process_2();

	if (pid_init == 0)
		pidns_process_init();

	if (pid_init > 0 && pid_2 > 0) {
		waitpid(pid_init, NULL, 0);
		waitpid(pid_2, NULL, 0);
	}

	return 0;
}

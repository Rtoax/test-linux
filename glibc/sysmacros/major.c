#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <linux/major.h>

#define TASK_COMM_LENGTH 16

struct __proc_stat {
	pid_t pid;
	char comm[TASK_COMM_LENGTH+1];
	char state;
	pid_t ppid, sid, pgid;
	dev_t ctty;
};

#define __assert_nonzero(expr) ({					\
		typeof(expr) __val = expr;				\
		if (__val == 0)						\
			__die("Unexpected: %s == 0!\n", #expr);		\
		__val;							\
	})

void __die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(1);
}

int __parse_proc_stat(int statfd, struct __proc_stat *out)
{
	char buf[1024];
	int n;
	unsigned dev;
	lseek(statfd, 0, SEEK_SET);
	if (read(statfd, buf, sizeof buf) < 0)
		return __assert_nonzero(errno);
	n = sscanf(buf, "%d (%16[^)]) %c %d %d %d %u",
			&out->pid, out->comm,
			&out->state, &out->ppid, &out->pgid,
			&out->sid, &dev);
	if (n == EOF)
		return __assert_nonzero(errno);
	if (n != 7) {
		return EINVAL;
	}
	out->ctty = dev;

	return 0;
}

int main(void)
{
	int statfd;
	char stat_path[256];
	struct __proc_stat child_status;

	snprintf(stat_path, sizeof stat_path, "/proc/%d/stat", getpid());
	statfd = open(stat_path, O_RDONLY);

	__parse_proc_stat(statfd, &child_status);

	printf("ChildStatus: pid    = %d\n", child_status.pid);
	printf("ChildStatus: comm   = %s\n", child_status.comm);
	printf("ChildStatus: state  = %d\n", child_status.state);
	printf("ChildStatus: ppid   = %d\n", child_status.ppid);
	printf("ChildStatus: sid    = %d\n", child_status.sid);
	printf("ChildStatus: pgid   = %d\n", child_status.pgid);
	printf("ChildStatus: ctty   = %ld\n", child_status.ctty);

	if (major(child_status.ctty) != UNIX98_PTY_SLAVE_MAJOR) {
		printf("Child is not connected to a pseudo-TTY. Unable to steal TTY.\n");
		return EINVAL;
	}

	return 0;
}

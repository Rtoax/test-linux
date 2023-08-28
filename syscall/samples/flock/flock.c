#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <getopt.h>


enum {
	ARG_LOCK_MAND = 101,
};

static const char *filename = "testfile";
static int secs = 1;

#define OPERATION_ALL	\
	(LOCK_EX | LOCK_NB | LOCK_MAND | LOCK_READ | LOCK_WRITE)

void usage(int err)
{
	printf(
	"-h, --help      show this information\n" \
	"-f, --file      specify file to lock, default: %s\n" \
	"-s, --secs      hold lock for seconds, default: %d\n" \
	"--lock-mand     operation LOCK_MAND\n" \
	,
	filename,
	secs);

	exit(err);
}

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	int cmd, option_index;
	int operation = 0;

	static struct option options[] = {
		{"help",        no_argument,       0, 'h'},
		{"file",        required_argument, 0, 'f'},
		{"secs",        required_argument, 0, 's'},
		{"lock-mand",   no_argument,       0, ARG_LOCK_MAND},
		{0, 0, 0, 0}
	};

	while (1) {
		cmd = getopt_long(argc, argv, "hf:s:", options, &option_index);
		if (cmd == -1)
			break;
		switch (cmd) {
		case 'h':
			usage(0);
			break;
		case 'f':
			filename = optarg;
			break;
		case 's':
			secs = atoi(optarg);
			break;
		case ARG_LOCK_MAND:
			operation |= LOCK_MAND;
			break;
		default:
			abort();
			break;
		}
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	/* LOCK_RW = LOCK_READ | LOCK_WRITE */
	operation |= LOCK_EX | LOCK_NB;
	ret = flock(fd, operation);
	if (ret != 0) {
		fprintf(stderr, "flock: %s\n", strerror(errno));
		exit(1);
	}

	/* Hold flock for a little while */
	if (secs)
		sleep(secs);

	write(fd, "hello\n", sizeof("hello\n"));

	flock(fd, LOCK_UN);
	printf("Unlock %s\n", filename);

	close(fd);
	return 0;
}

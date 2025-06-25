#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <getopt.h>
#include <signal.h>
#include "list.h"


#define PROC_ROOT	"/proc"
#define MAX_PATH	512

struct path {
	char *path;
	struct list node;
};

static struct list proc_files;

int read_dir(const char *path)
{
	DIR *dir;
	struct dirent *child_dir;
	char path_child[MAX_PATH];

	dir = opendir(path);
	if (!dir) {
		if (errno == EACCES) {
			fprintf(stderr, "%s: %s\n", path, strerror(errno));
			fprintf(stderr, "Run with superuser, root maybe.\n");
			exit(1);
		} else if (errno == ENOENT || errno == ENOTDIR) {
			fprintf(stderr, "%s: %s\n", path, strerror(errno));
			/* skip */
			return -ENOENT;
		}
	}

	while (true) {
		if (!(child_dir = readdir(dir)))
			/* loop done */
			break;

		if (child_dir->d_type == DT_REG) {

			struct path *p = malloc(sizeof(struct path));

			snprintf(path_child, MAX_PATH, "%s/%s", path, child_dir->d_name);
			p->path = strdup(path_child);
			list_insert(&proc_files, &p->node);

		} else if (child_dir->d_type == DT_DIR) {

			/* skip '.' and '..' */
			if (strcmp(child_dir->d_name, ".") &&
				strcmp(child_dir->d_name, "..")) {

				snprintf(path_child, MAX_PATH, "%s/%s", path, child_dir->d_name);
				read_dir(path_child);
			}
		}
	}

	closedir(dir);

	return 0;
}

void print_files(void)
{
	struct path *iter;

	list_for_each_entry(iter, &proc_files, node) {
		printf("%s\n", iter->path);
	}
}

static unsigned int read_nloop = 1;

void read_files(void)
{
	int fd;
	struct path *iter;
	char buffer[64];
	unsigned int nloop = read_nloop ?: 1;

	while (nloop--) {
		list_for_each_entry(iter, &proc_files, node) {
			fd = open(iter->path, O_RDONLY);
			/* skip if open failed */
			if (fd == -1) {
				continue;
			}
			read(fd, buffer, 2);
			close(fd);
		}
	}
}

void *thread_fn(void *arg)
{
	read_files();

	return NULL;
}

static int nr_threads = 2;
pthread_t *threads;

void sig_handler(int signum)
{
	int i;

	switch (signum) {
	case SIGINT:
		printf("Catch CTRL+C.\n");
		for (i = 0; i < nr_threads; i++) {
			pthread_cancel(threads[i]);
		}
		break;
	default:
		break;
	}
}

void help(void)
{
	printf(
	"\n"
	"Usage: \n"
	"\n"
	" -h, --help       show this info\n"
	" -t, --thread     how many thread to create\n"
	"     --loop       print loop times\n"
	"\n"
	);

	exit(0);
}

void parse_args(int argc, char *argv[])
{
	struct option options[] = {
		{ "thread",    required_argument,   0,  't' },
		{ "loop",      required_argument,   0,  101 },
		{ "help",      no_argument,         0,  'h' },
		{ NULL },
	};

	while (true) {
		int idx = 0;
		char ch;
		ch = getopt_long(argc, argv, "t:h", options, &idx);
		if (ch < 0)
			break;

		switch (ch) {
		case 'h':
			help();
			break;
		case 't':
			nr_threads = atoi(optarg);
			break;
		case 101:
			read_nloop = atoi(optarg);
			break;
		default:
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	int i;

	parse_args(argc, argv);

	signal(SIGINT, sig_handler);

	list_init(&proc_files);

	read_dir(PROC_ROOT);

	printf("=========================\n");
	printf("=== Create %d threads\n", nr_threads);
	printf("=== nloop = %d\n", read_nloop);

	threads = malloc(sizeof(pthread_t) * nr_threads);
	for (i = 0; i < nr_threads; i++) {
		pthread_create(&threads[i], NULL, thread_fn, NULL);
	}

	/* wait wait wait.. i just wanna wait wait wait, what you waiting for? */
	for (i = 0; i < nr_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	free(threads);

	printf("Bye.\n");

	return 0;
}

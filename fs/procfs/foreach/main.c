/**
 * loop read /proc for testing
 *
 * 2023-03-14	Rong Tao	Create this.
 */
#define _GNU_SOURCE
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

void read_files(void)
{
	int fd;
	struct path *iter;
	char buffer[64];

	list_for_each_entry(iter, &proc_files, node) {
		fd = open(iter->path, O_RDONLY);
		/* skip if open failed */
		if (fd == -1) {
			fprintf(stderr, "open: %s: %s\n", iter->path, strerror(errno));
			continue;
		}
		read(fd, buffer, 2);
		close(fd);
	}
}

void *thread_fn(void *arg)
{
	read_files();

	return NULL;
}

int main(int argc, char *argv[])
{
	int i, nr_threads = 2;

	pthread_t *threads;

	list_init(&proc_files);

	read_dir(PROC_ROOT);

	threads = malloc(sizeof(pthread_t) * nr_threads);
	for (i = 0; i < nr_threads; i++) {
		pthread_create(&threads[i], NULL, thread_fn, NULL);
	}

	for (i = 0; i < nr_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}


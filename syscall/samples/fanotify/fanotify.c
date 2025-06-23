#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/fanotify.h>

#define FANOTIFY_BUFFER_SIZE	1024

/* Setup fanotify notifications (FAN) mask. All these defined in fanotify.h. */
static uint64_t event_mask = (FAN_ACCESS |	/* File accessed */
			      FAN_MODIFY |	/* File modified */
			      FAN_CLOSE_WRITE |	/* Writtable file closed */
			      FAN_CLOSE_NOWRITE |	/* Unwrittable file closed */
			      FAN_OPEN |	/* File was opened */
			      FAN_ONDIR |	/* We want to be reported of events in the directory */
			      FAN_EVENT_ON_CHILD);	/* We want to be reported of events in files of the directory */

void process_event(struct fanotify_event_metadata *event)
{
	if (event->mask & FAN_OPEN)
		printf("\tFAN_OPEN\n");
	if (event->mask & FAN_ACCESS)
		printf("\tFAN_ACCESS\n");
	if (event->mask & FAN_MODIFY)
		printf("\tFAN_MODIFY\n");
	if (event->mask & FAN_CLOSE_WRITE)
		printf("\tFAN_CLOSE_WRITE\n");
	if (event->mask & FAN_CLOSE_NOWRITE)
		printf("\tFAN_CLOSE_NOWRITE\n");
}

int main(void)
{
	int fd, ret;
	char buffer[FANOTIFY_BUFFER_SIZE];
	ssize_t length;
	struct fanotify_event_metadata *metadata;

	fd = fanotify_init(FAN_CLOEXEC, O_RDONLY | O_CLOEXEC | O_LARGEFILE);
	if (fd < 0) {
		perror("fanotify_init");
		exit(1);
	}

	/* Trigger: cat /ets/os-release */
	ret = fanotify_mark(fd, FAN_MARK_ADD, event_mask, AT_FDCWD, "/etc/");
	if (ret < 0) {
		perror("fanotify_mark");
		exit(1);
	}

	length = read(fd, buffer, FANOTIFY_BUFFER_SIZE);
	metadata = (struct fanotify_event_metadata *)buffer;

	while (FAN_EVENT_OK(metadata, length)) {
		process_event(metadata);
		metadata = FAN_EVENT_NEXT(metadata, length);
	}

	close(fd);

	return 0;
}

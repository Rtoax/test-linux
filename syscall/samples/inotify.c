#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <sys/inotify.h>
#include <signal.h>
#include <stdlib.h>


void sig_handler(int signum)
{
	printf("catch ctrl+c\n");
	exit(0);
}

static void _inotify_event_handler(struct inotify_event *event)
{
	static long int cnt_ops=0;

	cnt_ops++;

	printf("event->wd:		%d\n", event->wd);
	printf("event->mask:	0x%08x, %ld\n", event->mask, cnt_ops);
	printf("event->cookie:	0x%08x\n", event->cookie);
	printf("event->len:		%d\n", event->len);

	printf("event->name:	%s\n", event->name);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("%s [filename]\n", argv[0]);
		return -1;
	}
	signal(SIGINT, sig_handler);

	unsigned char buf[1024] = {0};

	struct inotify_event *event = NULL;

	int fd = inotify_init();

	int wd = inotify_add_watch(fd, argv[1], IN_ALL_EVENTS);

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(fd, &fds);

	int len, index = 0;

	while (1) {
		printf("--------------\n");
		if ((len = read(fd, &buf, sizeof(buf))) <= 0) {
			break;
		} else {
			index = 0;
			while (index < len) {
				event = (struct inotify_event *)(buf+index);
				_inotify_event_handler(event);
				index += sizeof(struct inotify_event) + event->len;
			}
		}
	}

	inotify_rm_watch(fd, wd);

	return 0;
}


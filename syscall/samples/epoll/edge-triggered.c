#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>

int main(void)
{
	int epfd, nfds;
	struct epoll_event event, events[5];
	char buf[256];

	epfd = epoll_create(1);

	event.data.fd = STDIN_FILENO;
	event.events = EPOLLIN | EPOLLET;
#ifdef USE_ONESHOT
	event.events |= EPOLLONESHOT;
#endif

	epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
	while (1) {
		nfds = epoll_wait(epfd, events, 5, -1);
		int i;
		for (i = 0; i < nfds; ++i) {
			if (events[i].data.fd == STDIN_FILENO) {
				read(STDIN_FILENO, buf, 1);
				printf("hello world\n");

				/* Modify */
#if 0
				event.data.fd = STDIN_FILENO;
				event.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, STDIN_FILENO,
					  &event);
#endif
			}
		}
#ifdef USE_ONESHOT
		/* Reset for oneshot */
		event.data.fd = STDIN_FILENO;
		event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
		epoll_ctl(epfd, EPOLL_CTL_MOD, STDIN_FILENO, &event);
#endif
	}
}

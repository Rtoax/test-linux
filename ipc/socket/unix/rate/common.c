#include "common.h"


int unsocket_server(const char *PATH)
{
	struct sockaddr_un srv_addr;

	int listen_fd, ret;

	listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		return -1;
	}
	srv_addr.sun_family = AF_UNIX;
	strncpy(srv_addr.sun_path, PATH, sizeof(srv_addr.sun_path)-1);

	unlink(PATH);

	ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret == -1) {
		close(listen_fd);
		unlink(PATH);
		return -1;
	}

	ret = listen(listen_fd, 1);
	if (ret == -1) {
		close(listen_fd);
		unlink(PATH);
		return -1;
	}

	chmod(PATH, 00777);
	return listen_fd;
}

int unsocket_client(const char *PATH)
{
	int connect_fd;
	int ret = 0;

	static struct sockaddr_un srv_addr;

	connect_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (connect_fd < 0) {
		return -1;
	} else {
		srv_addr.sun_family = AF_UNIX;
		strcpy(srv_addr.sun_path, UNIX_DOMAIN);

		ret = connect(connect_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
		if (ret == -1) {
			close(connect_fd);
			return -1;
		}
	}

	return connect_fd;
}

unsigned long int diff_timeval_usec(struct timeval *big, struct timeval *small)
{
	unsigned long int diffsec = big->tv_sec - small->tv_sec;
	unsigned long int diffusec = diffsec*1000000 + (big->tv_usec - small->tv_usec);
	return diffusec;
}

void printf_rate(const char *prefix, unsigned long bytes, unsigned long microsec)
{
	printf("%s rate %.3lf Mbits/sec\n", prefix, bytes * 8.0 / 1024 / 1024 * 1000000 / microsec);
}

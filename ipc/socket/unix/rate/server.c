#include "common.h"


int main(void)
{
	int listen_fd;
	int con_fd;
	int ret = 0;
	socklen_t len;
	int val = 1;
	struct sockaddr_un clt_addr;
	char buf[MSG_LENGTH];
	unsigned long nloop = 0;
	struct timeval start, end;
	unsigned long recv_bytes = 0;

	listen_fd = unsocket_server(UNIX_DOMAIN);

	len = sizeof(clt_addr);

	con_fd = accept(listen_fd, (struct sockaddr*)&clt_addr, &len);

	val = 1;
	setsockopt(listen_fd, SOL_TCP, TCP_NODELAY, &val, sizeof(val));
	setsockopt(con_fd, SOL_TCP, TCP_NODELAY, &val, sizeof(val));
	if (con_fd < 0) {
		perror("cannot accept client connect request.");
		close(listen_fd);
		unlink(UNIX_DOMAIN);
	}


	gettimeofday(&start, NULL);
	while (++nloop <= TEST_NLOOP) {
		ret = read(con_fd, buf, MSG_LENGTH);
		recv_bytes += ret;
	}
	gettimeofday(&end, NULL);
	printf_rate("Read", recv_bytes, diff_timeval_usec(&end, &start));

	close(con_fd);
	close(listen_fd);
	return 0;
}

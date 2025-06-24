#include "common.h"


int main(void)
{
	int connect_fd;
	int ret = 0;
	unsigned long nloop = 0;
	struct timeval start, end;
	unsigned long send_bytes = 0;
	int val = 1;
	char buf[MSG_LENGTH];


	connect_fd  = unsocket_client(UNIX_DOMAIN);
	setsockopt(connect_fd, SOL_TCP, TCP_NODELAY, &val, sizeof(val));

	gettimeofday(&start, NULL);
	while (++nloop <= TEST_NLOOP) {
		ret = write(connect_fd, buf, MSG_LENGTH);
		send_bytes += ret;
	}
	gettimeofday(&end, NULL);
	printf_rate("Send", send_bytes, diff_timeval_usec(&end, &start));

	close(connect_fd);
	return 0;
}

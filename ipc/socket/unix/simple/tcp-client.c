#include "common.h"

int main(void)
{
	int connect_fd;
	int ret = 0;
	char buffer[128];
	struct sockaddr_un srv_addr;

	/* or AF_LOCAL */
	connect_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (connect_fd < 0) {
		perror("create socket error.");
		exit(1);
	}

	srv_addr.sun_family = AF_UNIX;
	strcpy(srv_addr.sun_path, UNIX_DOMAIN);

	ret = connect(connect_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret == -1) {
		close(connect_fd);
		exit(1);
	}

	printf("Send: %04x %04x %04x\n", recv_php_buf[0], recv_php_buf[1], recv_php_buf[2]);
	_print_buf(recv_php_buf, sizeof(recv_php_buf));
	write(connect_fd, recv_php_buf, sizeof(recv_php_buf));

	short recv_php_buf_send[3] = {
			htons(recv_php_buf[0]),
			htons(recv_php_buf[1]),
			htons(recv_php_buf[2]),
		};

	_print_buf(recv_php_buf_send, sizeof(recv_php_buf_send));
	write(connect_fd, recv_php_buf_send, sizeof(recv_php_buf_send));

#if 0
	fgets(buffer, sizeof(buffer), stdin);
	write(connect_fd, buffer, strlen(buffer) + 1);
#endif
#if 0
	while (1)
		sleep(3);
#endif
	(void)buffer;

	close(connect_fd);
	return 0;
}

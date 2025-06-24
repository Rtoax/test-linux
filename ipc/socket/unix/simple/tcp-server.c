#include "common.h"

int main(void)
{
	int listen_fd;
	int client_fd;
	int ret = 0;
	socklen_t len;
	struct sockaddr_un clt_addr, srv_addr;

	listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		perror("sreate listening socket error.");
		exit(1);
	}

	/* or AF_LOCAL */
	srv_addr.sun_family = AF_UNIX;
	strncpy(srv_addr.sun_path, UNIX_DOMAIN, sizeof(srv_addr.sun_path)-1);

	unlink(UNIX_DOMAIN);

	ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret == -1) {
		perror("cannot bind server socket.");
		close(listen_fd);
		unlink(UNIX_DOMAIN);
		exit(1);
	}

	ret = listen(listen_fd, 1);
	if (ret == -1) {
		perror("cannot listen the client connect request.");
		close(listen_fd);
		unlink(UNIX_DOMAIN);
		exit(1);
	}

	chmod(UNIX_DOMAIN, 0777);

	while (1) {
		len = sizeof(clt_addr);
		client_fd = accept(listen_fd, (struct sockaddr*)&clt_addr, &len);
		if (client_fd < 0) {
			perror("cannot accept client connect request.");
			close(listen_fd);
			unlink(UNIX_DOMAIN);
			break;
		}
		memset(recv_php_buf, 0, sizeof(recv_php_buf));
		recv_php_num = read(client_fd, recv_php_buf, sizeof(recv_php_buf));
		_print_buf(recv_php_buf, sizeof(recv_php_buf));
		printf("\n");
#if defined(NO_CLOSE_CLIENT_FD)
# pragma message "TEST: Do not close client fd"
#else
		close(client_fd);
#endif
	}

	return 0;
}

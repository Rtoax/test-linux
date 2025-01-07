#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char buf[128], *ip_addr;
	socklen_t len;
	struct sockaddr_in addr;

	if (argc >= 2)
		ip_addr = argv[1];
	else
		ip_addr = "127.0.0.1";

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip_addr);
	len = sizeof(struct sockaddr_in);

	if (getnameinfo((struct sockaddr *)&addr, len, buf, sizeof(buf),
			NULL, 0, NI_NAMEREQD)) {
		printf("Could not resolve reverse lookup of hostname\n");
		return -errno;
	}

	printf("Hostname: %s\n", buf);

	return 0;
}

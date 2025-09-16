/**
 * int getaddrinfo(const char *restrict node,
 *                 const char *restrict service,
 *                 const struct addrinfo *restrict hints,
 *                 struct addrinfo **restrict res);
 *
 * int getaddrinfo_a(int mode, struct gaicb *list[restrict],
 *                   int nitems, struct sigevent *restrict sevp);
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void)
{
	int rc;
	struct addrinfo hints, *res = NULL;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	rc = getaddrinfo("127.0.0.1", "123", &hints, &res);
	if(rc != 0) {
		perror("getaddrinfo error");
		exit(1);
	}
	printf("getaddrinfo success\n");
	return 0;
}


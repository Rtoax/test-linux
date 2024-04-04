#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

const char *tl_inet_ntop(int family, const void *src, char *dst, size_t len)
{
	const u_char *p = (const u_char *)src;

	if (family == AF_INET) {
		char temp[INET_ADDRSTRLEN];

		snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0],p[1],p[2],p[3]);

		if (strlen(temp) >= len) {
			errno = ENOSPC;
			return NULL;
		}
		strcpy(dst, temp);
		return dst;
	}
	errno = EAFNOSUPPORT;
	return NULL;

}

int main(void)
{
	return 0;
}

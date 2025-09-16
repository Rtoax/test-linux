/**
 * int gethostbyname_r(const char *restrict name,
 *                     struct hostent *restrict ret,
 *                     char buf[restrict .buflen], size_t buflen,
 *                     struct hostent **restrict result,
 *                     int *restrict h_errnop);
 *
 * int gethostbyname2_r(const char *restrict name, int af,
 *                      struct hostent *restrict ret,
 *                      char buf[restrict .buflen], size_t buflen,
 *                      struct hostent **restrict result,
 *                      int *restrict h_errnop);
 */
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>

#include "netdb_helpers.h"


struct hostent *tl_gethostname(char *host)
{
	struct hostent hostbuf, *hp;
	size_t hstbuflen;
	char *tmphstbuf;
	int res;
	int herr;

	hstbuflen = 1024;

	/* Allocate buffer, remember to free it to avoid memory leakage. */
	tmphstbuf = malloc(hstbuflen);
	while ((res = gethostbyname_r(host, &hostbuf, tmphstbuf, hstbuflen,
					&hp, &herr)) == ERANGE)
	{
		/* Enlarge the buffer. */
		hstbuflen *= 2;
		tmphstbuf = realloc(tmphstbuf, hstbuflen);
	}
	/* Check for errors. */
	if (res || hp == NULL)
		return NULL;
	return hp;
}

int main(void)
{
	struct hostent *host, hostbuf;
	const char name[] = "www.baidu.com";
	char buffer[1024];
	int err;

	gethostbyname_r(name, &hostbuf, buffer, sizeof(buffer), &host, &err);
	print_hostent(host);

	gethostbyname2_r(name, AF_INET, &hostbuf, buffer, sizeof(buffer), &host,
			 &err);
	print_hostent(host);

	return 0;
}

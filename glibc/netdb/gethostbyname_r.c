#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>

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
	return 0;
}

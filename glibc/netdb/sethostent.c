#include <netdb.h>
#include <stdio.h>

int main(void)
{
	sethostent(1);

	struct hostent *host = gethostent();

	printf("%s\n", host->h_name);

	endhostent();

	return 0;
}

#include <stdio.h>
#include <netdb.h>

int main(void)
{
	printf("%s\n", gai_strerror(0));
	return 0;
}

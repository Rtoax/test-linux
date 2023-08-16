#include <stdio.h>
#include <unistd.h>


int main(void)
{
	char buf[64];
	ttyname_r(fileno(stderr), buf, sizeof(buf));
	printf("%s\n", buf);
	return 0;
}

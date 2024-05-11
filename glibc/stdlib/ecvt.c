#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int d, n;
	char *s;

	s = ecvt(-12312.11300, 11, &d, &n);
	printf("s = %s, d = %d, n = %d\n",s,  d, n);

	return 0;
}

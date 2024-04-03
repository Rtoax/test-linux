#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ret;
	ret = sysconf(_SC_PAGESIZE);
	printf("%d\n", ret);
	return 0;
}

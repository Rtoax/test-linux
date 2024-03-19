#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int ret = getdtablesize();
	printf("getdtablesize = %d\n", ret);
	return 0;
}


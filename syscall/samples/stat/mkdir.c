#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	int ret = mkdir("rong.out", 0777);
	printf("ret: %d\n", ret);
	return 0;
}

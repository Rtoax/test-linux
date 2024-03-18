#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int ret;

	ret = mkdir("rong.out", 0777);
	printf("mkdir ret: %d\n", ret);

	ret = rmdir("rong.out");
	printf("rmdir ret: %d\n", ret);

	return 0;
}

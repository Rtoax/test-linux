#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int ret;
	ret = printf("rongtao\n");
	ret = execl("/bin/ls", "-l", "/etc/", NULL);
	printf("ret = %d\n", ret);
	return 0;
}

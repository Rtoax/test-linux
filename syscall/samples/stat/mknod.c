#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
	int ret = mknod("mknod.nod.out",  S_IFCHR, 0);
	printf("%d\n", ret);
	perror("mknod");
	return 0;
}

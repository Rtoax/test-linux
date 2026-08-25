#include <stdio.h>
#include <sys/sysmacros.h>
#include <sys/types.h>

int main(void)
{
	dev_t dev = makedev(1, 2);
	printf("%d:%d\n", major(dev), minor(dev));
	return 0;
}

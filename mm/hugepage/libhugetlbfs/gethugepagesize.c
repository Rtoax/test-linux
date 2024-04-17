#include <stdio.h>
#include <hugetlbfs.h>

int main(void)
{
	long ret = gethugepagesize();
	printf("gethugepagesizes ret = %d.\n", ret);
	return 0;
}

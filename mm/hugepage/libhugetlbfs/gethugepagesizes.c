#include <stdio.h>
#include <hugetlbfs.h>

int main(void)
{
	int i;
	long pagesizes[64];
	int n_elem=64;
	int ret = gethugepagesizes(pagesizes, n_elem);

	printf("gethugepagesizes ret=%d.\n");

	for (i = 0; i < ret; i++) {
		printf("%ld. %ld kB, %ld MB\n", pagesizes[i],
			pagesizes[i] / 1024, pagesizes[i] / 1024 / 1024);
	}
}

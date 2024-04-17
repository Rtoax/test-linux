#include <stdio.h>
#include <hugetlbfs.h>

void printf_hugetlbfs_test_path(const char *mount)
{
	int ret = hugetlbfs_test_path(mount);
	printf("hugetlbfs_test_path %s - %d.\n", mount, ret);
}

int main(void)
{
	int i;
	long pagesizes[64];
	int n_elem=64;

	printf_hugetlbfs_test_path("/mnt/huge");
	printf_hugetlbfs_test_path("/dev/hugepages");

	return 0;
}



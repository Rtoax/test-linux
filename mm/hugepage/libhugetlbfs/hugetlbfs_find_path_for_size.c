#include <stdio.h>
#include <hugetlbfs.h>


int main(void)
{
	int i;
	long pagesizes[64];
	int n_elem=64;
	int ret = getpagesizes(pagesizes, n_elem);

	printf("getpagesizes ret=%d.\n");

	for (i = 0; i < ret; i++) {
		const char *path = hugetlbfs_find_path_for_size(pagesizes[i]);
		printf("hugetlbfs_find_path_for_size path=%s.\n", path);
		printf("%s >> %ld. %ld kB, %ld MB\n", path,
			pagesizes[i], pagesizes[i] / 1024, pagesizes[i] / 1024 / 1024);
	}
	return 0;
}

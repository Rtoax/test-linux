#include <stdio.h>
#include <hugetlbfs.h>


int main(void)
{
	const char *path = hugetlbfs_find_path();
	printf("hugetlbfs_find_path path=%s.\n", path);
	return 0;
}

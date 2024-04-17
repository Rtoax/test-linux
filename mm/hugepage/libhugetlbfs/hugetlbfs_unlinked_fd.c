#include <stdio.h>
#include <hugetlbfs.h>

int main(void)
{
	int fd = hugetlbfs_unlinked_fd();
	printf("hugetlbfs_unlinked_fd fd=%d.\n", fd);
	return 0;
}





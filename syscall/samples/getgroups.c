#include <stdio.h>
#include <unistd.h>
#include <grp.h>
#include <sys/types.h>


int main(void)
{
	gid_t list[3];

	getgroups(3, list);

	printf("list[0]=%d\n", list[0]);
	printf("list[1]=%d\n", list[1]);
	printf("list[2]=%d\n", list[2]);

	return 0;
}

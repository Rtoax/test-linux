#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <grp.h>


int main(void)
{
	int i, nr;
	gid_t *list;

	nr = getgroups(0, NULL);

	list =(gid_t *)malloc(nr * sizeof(gid_t));

	getgroups(nr, list);

	for (i = 0; i < nr; i++)
		printf("list[%d]=%d\n", nr, list[0]);

	free(list);

	return 0;
}

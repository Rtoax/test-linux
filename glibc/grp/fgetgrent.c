#include <stdio.h>
#include <grp.h>


int main(void)
{
	FILE *fp = fopen("/etc/group", "r");

	struct group *group;
	while ((group = fgetgrent(fp)) != NULL) {
		printf("%s:%d:%s\n", group->gr_name, group->gr_gid, group->gr_mem[0]);
		group = NULL;
	}
	return 0;
}

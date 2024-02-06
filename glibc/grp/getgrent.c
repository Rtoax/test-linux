#include <stdio.h>
#include <grp.h>


int main(void)
{
	setgrent();
	struct group *group = getgrent();
	printf("%s:%d:%s\n", group->gr_name, group->gr_gid, group->gr_mem[0]);
	endgrent();
	return 0;
}

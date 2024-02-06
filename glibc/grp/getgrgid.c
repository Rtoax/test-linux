#include <stdio.h>
#include <sys/types.h>
#include <grp.h>
#include <unistd.h>


int main(void)
{
	int i = 0;
	struct group *_group = getgrgid(getgid());
	char **members = _group->gr_mem;

	printf("%s:%d:", _group->gr_name, _group->gr_gid);

	while (members[i] != NULL) {
		printf("%s:", members[i]);
		i++;
	}
	printf("\n");
	return 0;
}

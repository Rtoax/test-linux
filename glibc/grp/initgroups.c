#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(void)
{
	char *_group = "rongtao";
	struct group *grp;

	gid_t gr_gid;

	grp = getgrnam(_group);
	if (grp == NULL) {
		printf("getgrnam(\"%s\") failed, %s\n", _group, strerror(errno));
		return -1;
	}

	gr_gid = grp->gr_gid;

	if (initgroups("rongtao", gr_gid) == -1) {
		printf("initgroups(%s, %d) failed, %s\n","rongtao",
			gr_gid, strerror(errno));
	}
	return 0;
}

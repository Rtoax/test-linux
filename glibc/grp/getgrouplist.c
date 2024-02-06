#include <unistd.h>
#include <sys/types.h>
#include <malloc.h>
#include <pwd.h>
#include <grp.h>


gid_t *supplementary_groups(char *user)
{
	int igroups, ngroups = 16;

	gid_t *groups = (gid_t *)malloc(ngroups * sizeof(gid_t));
	struct passwd *pw = getpwnam(user);
	if (pw == NULL)
		return NULL;

	printf("%s\n", pw->pw_name);

	if (getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups) < 0) {
		groups = realloc(groups, ngroups * sizeof (gid_t));
		getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);
	}
	for (igroups = 0; igroups < ngroups; igroups++) {
		struct group *_group = getgrgid(groups[igroups]);
		printf("%s:%s:%d:\n", _group->gr_name, pw->pw_name, _group->gr_gid);
	}
	return groups;
}

int main(void)
{
	supplementary_groups("rongtao");
	return 0;
}

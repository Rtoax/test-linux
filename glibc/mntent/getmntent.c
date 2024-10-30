#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>

int main(void)
{
	struct mntent *ent;
	FILE *fp;

	fp = setmntent("/proc/mounts", "r");
	if (fp == NULL) {
		perror("setmntent");
		exit(1);
	}
	while (NULL != (ent = getmntent(fp))) {
		printf("mnt_fsname:%s mnt_dir: %s mnt_type:%s mnt_opts: %s\n",
			ent->mnt_fsname, ent->mnt_dir,
			ent->mnt_type, ent->mnt_opts);
	}
	endmntent(fp);

	return 0;
}


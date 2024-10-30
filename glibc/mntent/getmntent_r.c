#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>

int main(void)
{
	struct mntent *ent;
	FILE *fp;
	struct mntent mntbuf;
	char buf[512] = {0};

	fp = setmntent("/proc/mounts", "r");
	if (fp == NULL) {
		perror("setmntent");
		exit(1);
	}
	while (NULL != (ent = getmntent_r(fp, &mntbuf, buf, 512))) {
		printf("mnt_fsname:%s(%p) mnt_dir: %s mnt_type:%s mnt_opts: %s\n",
			ent->mnt_fsname, ent->mnt_fsname, ent->mnt_dir,
			ent->mnt_type, ent->mnt_opts);
		printf("%s\n", buf);
	}
	endmntent(fp);

	return 0;
}



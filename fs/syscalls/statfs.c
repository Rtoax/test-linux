#include <stdio.h>
#include <string.h>
#include <sys/statfs.h>

int main(void)
{
	int i, ret;
	struct statfs info;

	char *fss[] = {
		"/",
		"/dev",
		"/dev/shm",
		"/dev/mapper",
		"/run",
		"/sys/fs/cgroup",
		"/boot",
		"/work",

		"/home",
		"/home/rongtao",

		NULL,
	};

	fprintf(stdout, "%-15s %-12s %-12s %-12s\n",
		"FILE", "ALL(MB)", "FREE(MB)", "USE%");

	for (i = 0; fss[i] != NULL; i++) {
		memset(&info, 0, sizeof(struct statfs));

		ret = statfs(fss[i], &info);
		if (ret == -1)
			continue;

		unsigned long long total_sz = info.f_bsize * info.f_blocks;
		size_t total_sz_MB = total_sz >> 20;
		unsigned long long free_sz = info.f_bfree * info.f_bsize;
		size_t free_sz_MB = free_sz >> 20;

		printf("%-15s %-12ld %-12ld %-6.2lf%%\n",
			fss[i],
			total_sz_MB, free_sz_MB,
			(total_sz_MB - free_sz_MB) * 1.0 / total_sz_MB * 100.0);
	}

	return 0;
}

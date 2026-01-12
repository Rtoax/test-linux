#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>
#include <errno.h>
#include <malloc.h>

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#ifndef __USE_XOPEN_EXTENDED
#define __USE_XOPEN_EXTENDED
#endif

int display_ftw(const char *fpath, const struct stat *sb, int tflag,
		struct FTW *ftwbuf)
{
	printf("%-3s %2d ",
		(tflag == FTW_D) ? "d" :
		(tflag == FTW_DNR) ? "dnr" :
		(tflag == 5/*FTW_DP*/) ? "dp" :
		(tflag == FTW_F) ? "f" :
		(tflag == FTW_NS) ? "ns" :
		(tflag == FTW_SL) ? "sl" :
		(tflag == 6/*FTW_SLN*/) ? "sln" : "???",
		ftwbuf->level);

	if (tflag == FTW_NS) {
		printf("-------");
	} else {
		printf("%7jd", (intmax_t)sb->st_size);
	}
	printf("   %-40s %3d %s\n", fpath, ftwbuf->base, fpath+ftwbuf->base);

	return 0;
}

int main(int argc, char *argv[])
{
	int flags = 0;

	if (argc > 2 && strchr(argv[2], 'd') != NULL) {
		flags |= FTW_DEPTH;
	}
	if (argc > 2 && strchr(argv[2], 'p') != NULL) {
		flags |= FTW_PHYS;
	}

	if (nftw((argc < 2) ? "." : argv[1], display_ftw, 20, flags)) {
		perror("nftw");
		exit(1);
	}

	return 0;
}

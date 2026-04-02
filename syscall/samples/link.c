#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int ret;
	FILE *fp;

	fp = fopen("rong.out", "w");
	fclose(fp);

	/* Make hard link (same inode) */
	ret = link("rong.out", "rong2.out");
	printf("link ret: %d\n", ret);

	unlink("rong.out");
	unlink("rong2.out");

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	char *dir = "rong.out";
	int modeall = 0;

	modeall |= S_ISUID | S_ISGID | S_ISVTX;
	modeall |= S_IRUSR | S_IWUSR | S_IXUSR;
	modeall |= S_IRGRP | S_IWGRP | S_IXGRP;
	modeall |= S_IROTH | S_IWOTH | S_IXOTH;

	printf("modeall = %x\n", modeall);
	printf("0777 = %x\n", 0777);

	mkdir(dir, 0777);

	/* x for all */
	chmod(dir, S_IXUSR | S_IXGRP | S_IXOTH);

	chmod(dir, modeall);

	return 0;
}

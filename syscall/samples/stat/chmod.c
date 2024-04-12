#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	char *dir = "rong.out";

	mkdir(dir, 0777);

	/* x for all */
	chmod(dir, S_IXUSR | S_IXGRP | S_IXOTH);

	chmod(dir,
		S_ISUID | S_ISGID | S_ISVTX | S_IRUSR | S_IWUSR | S_IXUSR |
		S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

	return 0;
}

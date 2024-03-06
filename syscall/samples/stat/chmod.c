#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	mkdir("rong.out", 0777);
	chmod("rong.out",
	      S_ISUID | S_ISGID | S_ISVTX | S_IRUSR | S_IWUSR | S_IXUSR |
	      S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
	return 0;
}

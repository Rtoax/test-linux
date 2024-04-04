#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
	DIR *dir = opendir("./");
	struct dirent *diren;

	while ((diren = readdir(dir))) {
		printf("%4ld: %s, %ld, %d\n",
			telldir(dir), diren->d_name, diren->d_fileno, diren->d_type);
	}

	closedir(dir);
	return 0;
}

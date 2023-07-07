#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void)
{
	DIR *dir = opendir("/home/rongtao/");
	struct dirent *diren;

	while ((diren = readdir(dir))) {
		printf("%s, %ld, %d\n", diren->d_name, diren->d_fileno, diren->d_type);
	}

	closedir(dir);

	return 0;
}

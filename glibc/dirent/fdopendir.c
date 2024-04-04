#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	const char *path = "/etc/";
	DIR *dir = opendir(path);
	struct dirent *diren;

	while ((diren = readdir(dir))) {
		printf("%s, %ld, %d\n", diren->d_name, diren->d_fileno, diren->d_type);
	}

	closedir(dir);

	int fd = open(path, O_RDONLY);

	dir = fdopendir(fd);

	while ((diren = readdir(dir))) {
		printf("%s, %ld, %d\n", diren->d_name, diren->d_fileno, diren->d_type);
	}

	closedir(dir);

	return 0;
}

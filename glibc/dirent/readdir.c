#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{
	DIR *dp;
	struct dirent *ep;

	dp = opendir("./");
	if (!dp) {
		perror("Couldn’t open the directory");
		exit(1);
	}

	while ((ep = readdir(dp)))
		puts(ep->d_name);

	closedir(dp);

	return 0;
}

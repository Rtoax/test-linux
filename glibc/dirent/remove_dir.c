#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


int remove_dir(const char *dir)
{
	char cur_dir[] = ".";
	char up_dir[] = "..";

	char dir_name[1024];
	DIR *dirp;
	struct dirent *dp;
	struct stat dir_stat;

	/* directory not exist */
	if (0 != access(dir, F_OK)) {
		return 0;
	}

	/*get attribution error*/
	if (0 > stat(dir, &dir_stat)) {
		perror("get directory stat error.");
		return -1;
	}

	/* regular file, delete */
	if (S_ISREG(dir_stat.st_mode)) {
		remove(dir);
		fprintf(stderr, "Delete file %s\n", dir);
	} else if(S_ISDIR(dir_stat.st_mode)) {
		dirp = opendir(dir);
		while ((dp = readdir(dirp))!= NULL) {
			if ((0 == strcmp(cur_dir, dp->d_name)) ||
				(0 == strcmp(up_dir, dp->d_name)) )
				continue;
			sprintf(dir_name, "%s/%s", dir, dp->d_name);
			remove_dir(dir_name);
		}
		closedir(dirp);
		rmdir(dir);
		fprintf(stderr, "Delete dir %s\n", dir);
	} else {
		perror("unknow file type!");
	}
	return 0;
}


int main(int argc, char *argv[])
{
	remove_dir("a.dir");
	return 0;
}

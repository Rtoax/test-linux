#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

int delete_file(const char *filename, ...)
{
	if (filename == NULL) {
		printf("invalid pointer.\n");
		return -1;
	}

	struct stat st;
	char tmp[strlen(filename) + 100];

	if (-1 == access(filename, F_OK)) {
		printf("%s doesn't exist.\n", filename);
		return -1;
	}

	if (-1 == access(filename, W_OK|R_OK|X_OK)) {
		chmod(filename, 0777);
	}

	stat(filename, &st);
	if (S_ISDIR(st.st_mode)) {
		sprintf(tmp, "rm -r %s", filename);
	} else {
		sprintf(tmp, "rm %s", filename);
	}
	system(tmp);
	printf("%s\n", tmp);

	/* handle the "..." */
	va_list arg;
	va_start(arg, filename);
	char *filenames;
	while (1) {
		filenames = va_arg(arg, char *);
		if (0 == access(filenames, F_OK)) {
			delete_file(filenames);
		} else
			break;
	}
	va_end(arg);
	return 0;
}

int main(void)
{
	system("touch 1.txt 2.txt 3.txt 4.txt");
	system("ls *.txt");
	delete_file("1.txt");
	system("ls *.txt");
	delete_file("2.txt", "3.txt", "4.txt");
	return 0;
}

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


size_t get_executable_path(char* buffer, size_t len)
{
	char* path_end;
	/* Read the target of /proc/self/exe. */
	if(readlink("/proc/self/exe", buffer, len) <= 0)
		return -1;
	/* Find the last occurrence of a forward slash, the path separator. */
	path_end = strrchr(buffer, '/');
	if(path_end == NULL)
		return -1;
	/* Advance to the character past the last slash. */
	++path_end;
	/* Obtain the directory containing the program by truncating the
	 * path after the last slash. */
	*path_end = '\0';
	/* The length of the path is the number of characters up through the
	 * last slash. */
	return(size_t)(path_end - buffer);
}

int main(void)
{
	char path[PATH_MAX];
	get_executable_path(path, sizeof(path));
	printf("this program is in the directory %s\n", path);
	return 0;
}


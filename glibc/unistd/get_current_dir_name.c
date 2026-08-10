/**
 * see also AT_FDCWD, opendir(3), readdir(2)
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char *gnu_getcwd(void)
{
	return get_current_dir_name();
}

int main(void)
{
	printf("%s\n", get_current_dir_name());
	return 0;
}

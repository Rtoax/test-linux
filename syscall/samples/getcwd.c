#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *cwd = getcwd(NULL, 0);

	printf("cwd = %s\n", cwd);

	return 0;
}

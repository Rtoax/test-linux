#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *cwd = getcwd(NULL, 0);
	printf("cwd = %s\n", cwd);

	char buffer[1024];
	getcwd(buffer, sizeof(buffer));
	printf("cwd = %s\n", buffer);

	chdir("/etc");
	getcwd(buffer, sizeof(buffer));
	printf("cwd = %s\n", buffer);

	return 0;
}

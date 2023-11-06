#include <unistd.h>
#include <stdio.h>


int ls(void)
{
	char *argv[] = {"ls", "-al", "/etc/passwd", NULL};
	char *envp[] = {"PATH=/bin", NULL};
	execve("/bin/ls", argv, envp);
	return 0;
}

int main(void)
{
	char *const argv[] = { "-e", NULL };
	char *const envp[] = { "ROOT=/", "PATH=/bin", NULL };
	execve("/bin/date", argv, envp);
	return 0;
}


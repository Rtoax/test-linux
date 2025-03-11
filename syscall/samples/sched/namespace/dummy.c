#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#if defined(TRY_FORK) || defined(TRY_VFORK)
void try_fork(void)
{
#ifdef TRY_VFORK
	pid_t pid = vfork();
#else
	pid_t pid = fork();
#endif
	if (pid == -1) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		char *argv[] = {"echo", "child", NULL};
		execvp(argv[0], argv);
	}
	wait(NULL);
}
#else
#define try_fork()
#endif

#if defined(TRY_POPEN)
void try_popen(void)
{
	char buf[128] = "uname -rm";
	char line[256] = {0};
	FILE *fp = popen(buf, "r");
	if (fp == NULL) {
		fprintf(stderr, "popen(%s) %m\n", buf);
		return;
	}
	while (fgets(line, 256, fp))
		printf("%s\n", line);
	pclose(fp);
}
#else
#define try_popen()
#endif

int main(int argc, char *argv[])
{
	unsigned long count = 0;
	while (1) {
		printf("Sleeping %ld s\n", count++);
		sleep(1);
		try_fork();
		try_popen();
	}
	return 0;
}

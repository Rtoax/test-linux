#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
	char *env;
	int ret;
	char env_path[1024];
	char cwd[512];

	getcwd(cwd, sizeof(cwd));
	env = getenv("PATH");
	snprintf(env_path, sizeof(env_path), "PATH=%s:%s", env, cwd);
	putenv(env_path);
	env = getenv("PATH");
	printf("env = %s\n", env);

	pid_t pid = fork();
	if (pid == 0) {
		/* Run my sleep script */
		char *argv[] = {
			"mysleep.sh",
			"2",
			NULL
		};
		ret = execvp(argv[0], argv);
		if (ret == -1) {
			printf("Failed.\n");
		}
	} else if (pid > 0) {
		waitpid(pid, NULL, __WALL);
	}

	return 0;
}

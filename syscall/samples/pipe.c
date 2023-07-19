#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int pipe_fd[2] = {0};

void *task_fn(void *arg)
{
	char buf[16] = {"Hello"};
	write(pipe_fd[1], buf, strlen(buf));
	return NULL;
}

int main(void)
{
	char buf[256] = {0};


	pipe(pipe_fd);

	pthread_t task;
	pthread_create(&task, NULL, task_fn, NULL);

	read(pipe_fd[0], buf, sizeof(buf));
	fprintf(stdout, "read: %s\n", buf);

	pthread_join(task, NULL);

	return 0;
}

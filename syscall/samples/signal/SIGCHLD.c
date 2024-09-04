/**
 * SIGCHLD信号产生的条件
 *
 * 1. 子进程终止时会向父进程发送SIGCHLD信号，告知父进程回收自己，但该信号的默认
 *    处理动作为忽略，因此父进程仍然不会去回收子进程，需要捕捉处理实现子进程的
 *    回收；
 * 2. 子进程接收到SIGSTOP（19）信号停止时；
 * 3. 子进程处在停止态，接受到SIGCONT后唤醒时。
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status = 0xffff;

void clean_up_child_process(int signal_number)
{
	/* Clean up the child process. */
	int status;
	wait(&status);

	printf("Parent get SIGCHLD.\n");
	/* Store its exit status in a global variable. */
	child_exit_status = status;
}

int main(void)
{
	int child_pid;
	struct sigaction sigchld_action;

	memset(&sigchld_action, 0, sizeof(sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction(SIGCHLD, &sigchld_action, NULL);

	child_pid = fork();
	if (child_pid == 0) {
		sleep(1);
		exit(0xff);
	} else if (child_pid > 0) {
		while (!WIFEXITED(child_exit_status)) {
			printf("Parent running...\n");
			usleep(100000);
		}
		printf("child status %d\n", WEXITSTATUS(child_exit_status));
	}

	return 0;
}

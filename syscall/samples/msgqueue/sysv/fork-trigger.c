#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


struct msg_form {
	int mtype;
	char mtext[256];
};

struct task_wait {
	char tmpfile[64];
};


int task_wait_init(struct task_wait *waitqueue, char *tmpfile)
{
	int fd;

	sprintf(waitqueue->tmpfile, "%s", tmpfile ?: "/tmp/key-XXXXXXX");

	if (tmpfile)
		return 0;

	fd = mkstemp(waitqueue->tmpfile);
	if (fd <= 0) {
		fprintf(stderr, "mkstemp: %s\n", strerror(errno));
		return -errno;
	}
	close(fd);

	return 0;
}

int task_wait_destroy(struct task_wait *waitqueue)
{
	return 0;
}

int task_wait_wait(struct task_wait *waitqueue)
{
	int msqid;
	key_t key;

	struct msg_form msg;

	if ((key = ftok(waitqueue->tmpfile, 123)) < 0) {
		perror("ftok error");
		exit(1);
	}

	if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1) {
		perror("msgget error");
		exit(1);
	}

	msgrcv(msqid, &msg, sizeof(msg), msg.mtype, 0);

	msgctl(msqid, IPC_RMID, NULL);

	return 0;
}

int task_wait_trigger(struct task_wait *waitqueue)
{
	int msqid;
	key_t key;
	struct msg_form msg;

	if ((key = ftok(waitqueue->tmpfile, 123)) < 0) {
		perror("ftok error");
		exit(1);
	}

	if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1) {
		perror("msgget error");
		exit(1);
	}

	msg.mtext[0] = 'q';
	msgsnd(msqid, &msg, sizeof(msg), 0);

	msgctl(msqid, IPC_RMID, NULL);

	return 0;
}

int main(int argc, char *argv[])
{
	pid_t pid;

	struct task_wait waitqueue;

	task_wait_init(&waitqueue, argc>1?argv[1]:NULL);

	if (argc > 1) {

		printf("CHILD: wait to done.\n");
		task_wait_wait(&waitqueue);
		printf("CHILD: done.\n");

	} else {

		pid = fork();
		if (pid == 0) {
			int ret;

			char *_argv[] = {
				argv[0],
				waitqueue.tmpfile,
				NULL,
			};
			printf("PARENT: fork one.\n");
			ret = execvp(_argv[0], _argv);
			if (ret == -1) {
				exit(1);
			}

		} else if (pid > 0) {

			// do something
			printf("PARENT: do 2s thing.\n");
			sleep(2);
			task_wait_trigger(&waitqueue);
			printf("PARENT: kick child.\n");
			waitpid(pid, NULL, 0);
		}
	}

	task_wait_destroy(&waitqueue);

	return 0;
}

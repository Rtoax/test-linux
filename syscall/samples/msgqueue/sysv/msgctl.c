#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSG_FILE "/etc/os-release"
#define PROG_ID 124

int main(void)
{
	int msqid;
	key_t key;

	key = ftok(MSG_FILE, PROG_ID);
	perror("ftok");
	printf("key: %d\n", key);

	msqid = msgget(key, IPC_CREAT | 0777);
	perror("msgget");

	printf("msqid: %d\n", msqid);
	printf("pid: %d\n", getpid());

	msgctl(msqid, IPC_RMID, NULL);
	perror("msgctl");

	return 0;
}

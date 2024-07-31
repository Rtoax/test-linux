#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSG_FILE "/etc/os-release"
#define PROG_ID 125

struct msg_form {
	long mtype;
	char mtext[64];
};

int main(void)
{
	int cnt, ret;
	int msqid;
	key_t key;
	struct msg_form msg;

	key = ftok(MSG_FILE, PROG_ID);
	perror("ftok");
	printf("key: %d\n", key);

	msqid = msgget(key, IPC_CREAT | 0777);
	perror("msgget");

	printf("msqid: %d\n", msqid);
	printf("pid: %d\n", getpid());

	cnt = 0;

	for (;;) {
		printf("Try send msg.\n");

		msg.mtype = 999;
		sprintf(msg.mtext, "hello, I'm server %d", getpid());
		ret = msgsnd(msqid, &msg, sizeof(msg) - sizeof(msg.mtype), IPC_NOWAIT);
		if (ret)
			break;
		cnt++;
	}

	printf("Success count %d(maybe number of msgmax) %m\n", cnt);
	msgctl(msqid, IPC_RMID, NULL);

	return 0;
}

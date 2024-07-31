#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "common.h"

int main(void)
{
	int msqid;
	key_t key;
	struct msg_form msg;

	if ((key = ftok(MSG_FILE, PROG_ID)) < 0) {
		perror("ftok error");
		exit(1);
	}

	printf("Message Queue - Server key is: %d\n", key);

	if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1) {
		perror("msgget error");
		exit(1);
	}

	printf("My msqid is: %d\n", msqid);
	printf("My pid is: %d\n", getpid());

	for (;;) {
		msg.mtype = 888;
		msgrcv(msqid, &msg, sizeof(msg) - sizeof(msg.mtype), msg.mtype, 0);

		if (msg.mtext[0] == 'q') {
			break;
		}
		msg_print("server", msg);

		msg.mtype = 999;
		sprintf(msg.mtext, "hello, I'm server %d", getpid());
		msg.f = 6.28;

		msgsnd(msqid, &msg, sizeof(msg) - sizeof(msg.mtype), 0);
	}
	return 0;
}

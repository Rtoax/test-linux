#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#include "common.h"

int main(void)
{
	int msqid;
	key_t key;
	struct msg_form msg;
	char ch = 'a';

	if ((key = ftok(MSG_FILE, PROG_ID)) < 0) {
		perror("ftok error");
		exit(1);
	}

	printf("Message Queue - Client key is: %d\n", key);

	if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1) {
		perror("msgget error");
		exit(1);
	}

	printf("My msqid is: %d\n", msqid);
	printf("My pid is: %d\n", getpid());

	for (;;) {
		ch = getchar();

		msg.mtype = 888;
		sprintf(msg.mtext, "%c: hello, I'm client %d", ch, getpid());
		msg.f = 3.14;
		msgsnd(msqid, &msg, sizeof(msg) - sizeof(msg.mtype), 0);

		if (ch == 'q')
			break;

		msg.mtype = 999;
		msgrcv(msqid, &msg, sizeof(msg) - sizeof(msg.mtype), msg.mtype, 0);
		msg_print("client: ", msg);
	}

	return 0;
}

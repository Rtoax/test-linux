#pragma once

#define MSG_FILE "/etc/os-release"
#define PROG_ID 123

typedef struct {
	int a;
	int b;
	int c;
} ptr_msg;

struct msg_form {
	long mtype;
	char mtext[256];
	float f;
	void *ptr;
};

int msg_print(const char *ptr, const struct msg_form msg)
{
	printf("--------\n");
	printf("%s: %ld", ptr, sizeof(msg));
	printf("%s: %s\n", ptr, msg.mtext);
	printf("%s: %f\n", ptr, msg.f);

	return 0;
}

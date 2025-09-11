#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "common.h"

int usage_client(int argc, char *argv[])
{
	printf("\033[1m  echo [cmd] > /proc/sysrq-trigger\033[m\n");
	printf("   [cmd]:\n");
#define trigger(cmd, discription)    printf("    %c - %s\n", cmd, discription);
#include "trigger-defs.h"
#undef trigger
	printf("\033[1m  Extra COMMAND:\033[m\n");
	printf("    HELP - show this message.\n");
	printf("    WRITEFILE - test write file to %s\n", WRITE_TMPFILE);

	return 0;
}

int parse_cmd(char *line, cmd_fn cfn, writefile_fn wfn, CMD_TYPE *cmd_type, int *_errno)
{
	char cmd = line[0];

	int ret = -1;

	*_errno = 0;
	*cmd_type = CMD_NONE;

	switch (cmd) {
#define trigger(cmd, dis) case cmd:
#include "trigger-defs.h"
#undef trigger
			/* callback cmd_fn */
			ret = cfn(cmd, _errno);
			*cmd_type = CMD_TRIGGER;
			break;
		default:
			ret = -1;
			break;
	}

	if (ret == -1) {
		if (strncmp(line, "HELP", 4) == 0) {
			usage_client(0, NULL);
		} else if (strncmp(line, "WRITEFILE", 9) == 0) {
			/* callback writefile_fn */
			ret = wfn(line, _errno);
			*cmd_type = CMD_WRITEFILE;
		} else {
			usage_client(0, NULL);
		}
	}
	return ret;
}

void daemonize(void)
{
	if (fork() != 0)
		/* parent exits */
		exit(0);
	/* create a new session */
	setsid();
}

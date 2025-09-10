#ifndef _COMMON_H
#define _COMMON_H

#include <errno.h>
#include <sys/time.h>

#define MAX_LINE       2048
#define PORT           0x1234
#define BACKLOG        10
#define LISTENQ        6666
#define MAX_CONNECT    20

#define WRITE_TMPFILE	"/tmp/tcp-proc-trigger-writefile.txt"

typedef enum {
	CMD_NONE = 0,
	CMD_TRIGGER,   //for echo [cmd] > /proc/sysrq-trigger
	CMD_WRITEFILE, //for write TIME to WRITE_TMPFILE
} CMD_TYPE;

const static char *CMD_STR[] = {
	[CMD_NONE] = "NONE",
	[CMD_TRIGGER] = "Trigger",
	[CMD_WRITEFILE] = "Writefile",
};

typedef int (*cmd_fn)(char cmd, int *_errno);
typedef int (*writefile_fn)(char *line, int *_errno);

void daemonize(void);
int tcpsocket_server();
int usage_client(int argc, char *argv[]);
int parse_cmd(char *line, cmd_fn cfn, writefile_fn wfn, CMD_TYPE *cmd_type, int *_errno);

static long int gettimeval(struct timeval *tv)
{
	gettimeofday(tv, NULL);
}

#endif /*<_COMMON_H>*/

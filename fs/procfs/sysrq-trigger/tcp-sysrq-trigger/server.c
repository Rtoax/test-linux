#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include "common.h"

int handle_sysrq_trigger(char *cmd, CMD_TYPE *cmd_type, int *_errno);

int main(int argc, char *argv[])
{
	//daemonize();

	struct sockaddr_in servaddr, cliaddr;

	int _errno = 0;
	CMD_TYPE cmd_type = CMD_NONE;
	int listenfd, connfd;
	pid_t childpid;
	char buf[MAX_LINE];

	socklen_t clilen;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	if (listen(listenfd, LISTENQ) < 0) {
		perror("listen error");
		exit(1);
	}

	char *tmp;

	while (1) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
			perror("accept error");
			exit(1);
		}

		ssize_t n;
		char buf[MAX_LINE];
		while ((n = read(connfd, buf, MAX_LINE)) > 0) {
			int cmd_rslt = -1;
			cmd_rslt = handle_sysrq_trigger(buf, &cmd_type, &_errno);
			if (cmd_rslt == 0) {
				sprintf(buf, "Success to %s", CMD_STR[cmd_type]);
			} else {
				sprintf(buf, "Failed to %s: %s", CMD_STR[cmd_type], strerror(_errno));
			}
			write(connfd, buf, strlen(buf)+1);
		}
		close(connfd);
	}
	close(listenfd);
}

int echo_proc_sysrq_trigger(char cmd, int *_errno)
{
	int n = 0;
	int fd;
	char str_cmd[4] = {0};

	*_errno = 0;

	fd = open("/proc/sysrq-trigger", O_RDWR | O_NONBLOCK | O_NDELAY);
	if (fd <= 0) {
		perror("open:");
		*_errno = errno;
		goto done;
	}
	printf("echo %c > /proc/sysrq-trigger\n", cmd);
	sprintf(str_cmd, "%c", cmd);
	n = write(fd, str_cmd, 1);
	if (n <= 0) {
		*_errno = errno;
	}

	close(fd);

done:
	return n > 0 ? 0 : -1;
}

int writefile_to_tmp(char *line, int *_errno)
{
	int ret = -1;

	char buffer[256];
	struct timeval tv;
	char *file = WRITE_TMPFILE;

	*_errno = 0;

	FILE *fp = fopen(file, "a+");
	if (!fp) {
		*_errno = errno;
		goto done;
	}
	gettimeofday(&tv, NULL);

	time_t t = time(NULL);

	strftime(buffer, 40, "EXEC time: %m-%d-%Y/%T", localtime(&tv.tv_sec));
	int n = fprintf(fp, "%s\n",buffer);
	ret = n > 0 ? 0 : -1;

	*_errno = errno;

	printf("write %s to %s\n", buffer, file);

	fclose(fp);
done:
	return ret;
}

int handle_sysrq_trigger(char *line, CMD_TYPE *cmd_type, int *_errno)
{
	return parse_cmd(line, echo_proc_sysrq_trigger, writefile_to_tmp, cmd_type, _errno);
}

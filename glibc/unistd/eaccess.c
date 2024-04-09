#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void sys_err(const char *msg)
{
	perror(msg);
	exit(-1);
}

int open_read_test(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		goto error_without_close;
	}

	close(fd);
	return 0;

error_without_close:
	return -1;
}

int access_read_test(const char *filename)
{
	return access(filename, R_OK);
}

int eaccess_read_test(const char *filename)
{
	return eaccess(filename, R_OK);
}

int main(int argc, char **args)
{
	const char *filename = "/etc/os-release";

	if (open_read_test(filename) < 0) {
		perror("open read perrmission test: FAIL");
	} else {
		printf("open read perrmission test: DONE\n");
	}

	if (access_read_test(filename) < 0) {
		perror("access read perrmission test: FAIL");
	} else {
		printf("access read perrmission test: DONE\n");
	}

	if (eaccess_read_test(filename) < 0) {
		perror("eaccess read perrmission test: FAIL");
	} else {
		printf("eaccess read perrmission test: DONE\n");
	}

	return 0;
}


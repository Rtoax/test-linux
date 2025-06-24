#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define UNIX_DOMAIN "./UNIX.sock"

static short recv_php_buf[] = {0x0102, 0x0304, 0x0506};
static int __attribute__((unused)) recv_php_num = 0;

#define _print_buf(buf, size) \
	do { \
		int i = 0; char *_p = (char*)buf; \
		printf("BUF: "); \
		for (i = 0; i < size; i++) { \
			printf("%02x ", *_p); _p++; \
		} \
		printf("\n"); \
	} while (0)

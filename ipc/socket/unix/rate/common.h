#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
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
#include <netinet/tcp.h>

#define UNIX_DOMAIN "/tmp/UINX"

#ifndef TEST_SIZE
#define TEST_SIZE   1024
#endif
#ifndef TEST_NLOOP
#define TEST_NLOOP   102400
#endif

#define MSG_LENGTH          TEST_SIZE

#define MAX_CLIENT_NUM      10

#define debug() printf("%s:%d\n", __func__, __LINE__)

int unsocket_server(const char *PATH);
int unsocket_client(const char *PATH);
unsigned long int diff_timeval_usec(struct timeval *big, struct timeval *small);
void printf_rate(const char *prefix, unsigned long bytes, unsigned long microsec);

#endif /*<_COMMON_H>*/

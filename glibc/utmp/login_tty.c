#include <stdio.h>
#include <utmp.h>
#include <errno.h>


int main(void)
{
	FILE *fp;
	int ret;

	fp = fopen("/dev/pts/0", "r");

	ret = login_tty(fileno(fp));
	printf("ret = %d\n", ret);
	perror("login_tty.");

	return 0;
}


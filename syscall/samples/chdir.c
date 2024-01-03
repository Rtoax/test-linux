#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	chdir("/home/");
	system("ls; pwd");
	chdir("/etc/");
	system("ls; pwd");
	return 0;
}

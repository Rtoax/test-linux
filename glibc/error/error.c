#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	FILE *fp;
	if ((fp = fopen("__non_exist_file__", "rb")) == NULL) {
		error(2, errno, "RongTao:rong%d", 12312);
	}
	printf("printf:%s\n", strerror(errno));
	return 0;
}

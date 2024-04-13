#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	FILE *fp = NULL;
	if ((fp = fopen("__non_exist_file__", "rb")) == NULL) {
		error_at_line(0, errno, __FILE__, __LINE__, "rong %s", "tao");
	}
	printf("printf:%s\n", strerror(errno));
	return 0;
}

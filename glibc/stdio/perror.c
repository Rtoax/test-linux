#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	FILE *fp = NULL;
	if ((fp = fopen("__non_exist_file__", "rb")) == NULL) {
		perror("fopen");
	}
	printf("%s\n", strerror(errno));
	return 0;
}

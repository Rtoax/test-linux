#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "read_helpers.h"

int main(void)
{
	ssize_t n;
	char buf[64];

	while (1) {
		n = read(0, buf, sizeof(buf));
		if (n == -1) {
			fprintf(stderr, "%m\n");
			continue;
		}
		printf("%c", buf[0]);
	}

	return 0;
}

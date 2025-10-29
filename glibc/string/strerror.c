#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int i, nr, max_num = 0;

	printf("%d\n", errno);
	printf("%d:%s\n", errno, strerror(errno));
	printf("%d:%s\n", EPERM, strerror(EPERM));
	printf("%d:%s\n", EAGAIN, strerror(EAGAIN));

	for (i = 0, nr = 0; i < 256; i++) {
		if (strerror(i) != NULL &&
		    strncmp(strerror(i), "Unknown error", 13) != 0) {
			nr++;
			max_num = max_num < i ? i : max_num;
			printf("strerror(%d) = %s\n", i, strerror(i));
		    }
	}
	printf("nr = %d, max number is %d\n", nr, max_num);
	return 0;
}

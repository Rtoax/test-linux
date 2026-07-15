#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void base(void)
{
	printf("%d\n", errno);
	printf("%d:%s\n", errno, strerror(errno));
	printf("%d:%s\n", EPERM, strerror(EPERM));
	printf("%d:%s\n", EAGAIN, strerror(EAGAIN));
}

void all_errors(void)
{
	int i, nr, max_num = 0;

	for (i = 0, nr = 0; i < 256; i++) {
		if (strerror(i) != NULL &&
		    strncmp(strerror(i), "Unknown error", 13) != 0) {
			nr++;
			max_num = max_num < i ? i : max_num;
			printf("strerror(%d) = %s\n", i, strerror(i));
		    }
	}
	printf("nr = %d, max number is %d\n", nr, max_num);
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			int n = atoi(argv[i]);
			printf("%d:%s\n", n, strerror(n));
		}
	} else {
		base();
		all_errors();
	}
	return 0;
}

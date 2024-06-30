#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ret;
	struct timeval tv;
	struct timezone tz;

	printf("%d\n", gettimeofday(&tv, &tz));

	/* need root user do this */
	ret = settimeofday(&tv, &tz);
	if (ret) {
		fprintf(stderr, "settimeofday %m\n");
		exit(1);
	}

	return 0;
}

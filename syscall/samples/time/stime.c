#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main(void)
{
#if 0 /* FIXME: deprecated stime(2) */
	int ret;
	time_t t = time(NULL);
	printf("time: %ld\n", t);

	ret = stime(&t);
	if (ret == -1) {
		fprintf(stderr, "stime() %m\n");
		exit(1);
	}
#else
	fprintf(stderr, "stime() is deprecated.\n");
#endif
	return 0;
}


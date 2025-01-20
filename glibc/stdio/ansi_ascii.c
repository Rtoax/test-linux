#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED   "\033[31m"
#define GREEN "\x1b[32m"
#define CLEAR "\x1b[0m"

#define DEBUG_CHECK "\xe2\x9c\x92"
#define SUCCESS_CHECK "\xe2\x9c\x94"
#define FAILURE_CHECK "\xe2\x9c\x98"

static char mem[] = "\033";
static char *ansi[] = {
	RED, GREEN
};

int main(void)
{
	printf("size of \033 = %ld\n", sizeof(mem));

	/* Success */
	if (!memcmp(mem, "\033", 2))
		printf("==\n");

	/* Failed */
	if (!memcmp(ansi[0], "\033", 2))
		printf("==\n");

	fprintf(stderr, "%s\n", DEBUG_CHECK);
	fprintf(stderr, "\xe2\x9c\x92\n");
	fprintf(stderr, "\xe2\x9c\x93\n");
	fprintf(stderr, "\xe2\x9c\x94\n");
	fprintf(stderr, "\xe2\x9c\x95\n");
	fprintf(stderr, "\xe2\x9c\x96\n");
	fprintf(stderr, "\xe2\x9c\x97\n");
	fprintf(stderr, "\xe2\x9c\x98\n");
	fprintf(stderr, "\xe2\x9c\x99\n");

	fprintf(stderr, RED "123123" FAILURE_CHECK " %s\n" CLEAR, "RongTao");
	fprintf(stderr, "############");
	fprintf(stderr, RED "123123" SUCCESS_CHECK " %s\n" CLEAR, "RongTao");
	fprintf(stderr, "############");

	return 0;
}

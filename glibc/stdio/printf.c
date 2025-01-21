#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#if defined(M32)
# define PRId   PRId32
#else
# define PRId   PRId64
#endif

#define STR	"hello world"

int main(void)
{
	int i;

	printf("pid %d\n", getpid());
	printf("printf addr %p\n", &printf);

#ifdef LIBC_PRINTF_SYMADDR
	printf("LIBC_PRINTF_SYMADDR = 0x%x\n", LIBC_PRINTF_SYMADDR);
#endif

	for (i = 0; i <= strlen(STR); i++)
		printf("%3d/%" PRId "  [%.*s]\n", i, strlen(STR), i, STR);

	printf("KB/s \n");

	printf("%*.*d\n", 3, 10, 10);
	printf("%.*s\n", 4, "hello");
	printf("%*s\n", 40, "hell0");
	printf("%*.*s\n", 40, 4, "hell0");

	printf("%.*d\n", 4, 10000);
	printf("%*d\n", 40, 10000);
	printf("%*.*d\n", 40, 4, 10000);

	printf("Hello %.*d %.*d\n", 5, 2, 5, 3);
	return 0;
}

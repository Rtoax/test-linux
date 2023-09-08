#include <malloc.h>
#include <unistd.h>

int main(void)
{
	int i;
	char *a;
	const int pagesize = getpagesize();
	const int blk = pagesize * 10;

	while (1) {
		a = malloc(blk);
		for (i = 0; i < blk; i += pagesize)
			a[i] = 'a';
		/* No need to free(), just leak it. */
	}
	return 0;
}

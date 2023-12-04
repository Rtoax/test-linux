#include <string.h>
#include <stdint.h>
#include <sys/types.h>


void *tl_memset(void *s, int c, size_t n)
{
	size_t i;
	uint8_t *si = s;
	for (i = 0; i < n; i++)
		si[i] = c;
	return s;
}

int main(void)
{
	char buf[1024] = {'x'};

	memset(buf, 'z', sizeof(buf));
	return 0;
}

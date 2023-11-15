#include <string.h>

int main(void)
{
	char buf[1024] = {'x'};
	char buf2[1024];

	memcpy(buf2, buf, sizeof(buf));
	return 0;
}

#include <string.h>

int main(void)
{
	char buf[1024] = {'x'};
	char buf2[1024] = {'z'};

	bcopy(buf, buf2, sizeof(buf));
	return 0;
}

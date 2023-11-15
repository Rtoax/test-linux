#include <string.h>

int main(void)
{
	char buf[1024] = {'x'};

	memset(buf, 'z', sizeof(buf));
	return 0;
}

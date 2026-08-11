#include <string.h>

int main(void)
{
	char buf[1024] = { 'x' };

	bzero(buf, sizeof(buf));
	return 0;
}

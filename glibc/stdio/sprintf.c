#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	int err;
	char buffer[8];

	err = sprintf(buffer, "%s", "1234567890");

	printf("%d %s\n", err, buffer);
	return 0;
}

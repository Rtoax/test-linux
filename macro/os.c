#include <stdio.h>

int main(void)
{
	/* see os.mk */
	printf("ID=%s\n", OS_ID);
	printf("VERSION_ID=%d\n", OS_VERSION_ID);
	return 0;
}

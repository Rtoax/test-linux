#include <stdio.h>
#include "__stringify.h"

int main(void)
{
	/* see os.mk */
	printf("ID=%s\n", __stringify(OS_ID));
#if OS_ID == fedora
#pragma message "fedora"
	printf("OS is Fedora\n");
#endif
	printf("VERSION_ID=%d\n", OS_VERSION_ID);
	return 0;
}

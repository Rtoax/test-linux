#include <stdio.h>

#ifdef UNINITIALIZED_VALUES
int uninitialized_i;
int *uninitialized_ip;
char *uninitialized_s;
#endif

int main(void)
{
	printf("Hello World!\n");
	return 0;
}

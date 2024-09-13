#include <unistd.h>

int main(void)
{
	while (1)
#ifdef WHILE_SLEEP
		sleep(1)
#endif
		;
	return 0;
}

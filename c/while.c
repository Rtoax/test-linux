#include <stdio.h>
#include <unistd.h>

/**
 * if initialized with 0, is in .bss
 * if initialized with none 0, is in .data
 * if const, is in .rodata
 */
unsigned long bss_count = 0;
unsigned long data_count = 1;
const unsigned long rodata_count = 1;

int main(void)
{
	while (1)
#ifdef WHILE_SLEEP
	{
		printf("count %ld, %ld, %ld\n", bss_count++, data_count++,
		       rodata_count);
		sleep(1);
	}
#endif
		;
	return 0;
}

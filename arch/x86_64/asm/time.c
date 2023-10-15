#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t tt;
	struct tm *t;

	asm volatile (
		"mov $0, %%ebx\n\t"	/* time(NULL)'s NULL */
		"mov $0xd, %%eax\n\t"	/* time number syscall */
		"int $0x80\n\t"
		"mov %%eax, %0\n\t"
		: "=m" (tt)
	);

	t = localtime(&tt);
	printf("Year %d\n", t->tm_year + 1900);

	return 0;
}

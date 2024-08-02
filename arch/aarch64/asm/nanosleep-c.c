#include <string.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	int ret;
	struct timespec ts = {1, 0};

	/* int nanosleep(const struct timespec *req, struct timespec *rem); */
	__asm__("stp x0, x1, [sp, #-16]! \n\t"
		"mov x0, %[pts] \n\t"
		"mov x1, %[rem] \n\t"
		"mov x8, #0x65 \n\t"
		"svc #0 \n\t"
		"ldp x0, x1, [sp], #16 \n\t"
		: "=g"(ret)
		: [pts] "r"(&ts),
		  [rem] "g"(0));

	printf("exit.\n");

	return 0;
}

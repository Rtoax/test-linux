#include <stdio.h>
#include <sys/personality.h>

int main(void)
{
	int ret;
	unsigned long persona;

	/* FIXME: value ?? */
	persona = 0;
	ret = personality(persona);

	printf("ret = %d, persona = %#010lx\n", ret, persona);
	return 0;
}


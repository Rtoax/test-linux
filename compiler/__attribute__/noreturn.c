#include <stdio.h>
#include <stdlib.h>


__attribute__((noreturn)) void fun(char *str)
{
	if (str != NULL)
		printf("%s\n", str);
#ifdef ERROR
	/* Could not call return statement if noreturn */
	return;
#endif

#ifndef ERROR
	exit(0);
#endif

	/* noreturn function does return */
}

int main(void)
{
	fun("asdf");
	fun(NULL);

	return 0;
}

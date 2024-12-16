#include <stdio.h>


__attribute__((noreturn)) void fun(char *str)
{
	if (str != NULL)
		printf("%s\n", str);
	/* Could not call return */
	// return;
}

int main(void)
{
	fun("asdf");
	fun(NULL);

	return 0;
}

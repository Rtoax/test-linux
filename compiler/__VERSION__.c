#include <stdio.h>

int main(void)
{
	/* This macro expands to a string constant which describes the version
	 * of the compiler in use. You should not rely on its contents having
	 * any particular form, but it can be counted on to contain at least
	 * the release number. */
	printf("%s\n", __VERSION__);
	return 0;
}

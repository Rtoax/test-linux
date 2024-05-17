#include <stdio.h>
#include <nl_types.h>

int main(void)
{
	nl_catd catdesc = catopen("hello.cat", NL_CAT_LOCALE);
	printf(catgets(catdesc, 1, 1, "Hello, world!\n"));
	catclose(catdesc);
	return 0;
}

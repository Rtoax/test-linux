#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define failed(message) do {	\
		fprintf(stderr, "%s\n", message);	\
		exit(1);	\
	} while (0)

int main(void)
{
	if (strspn("123th", "123456789") != 3)
		failed("strspn");

	if (strcspn("1234,abc,567", " ,;") != 4)
		failed("strcspn");

	return 0;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = {'q', '2', '3', '\0'};

	char *ch = index(str, '2');
	printf("%p, %p\n", &str[1], ch);

	char *ch2 = rindex(str, '2');
	printf("%p, %p\n", &str[1], ch2);

	return 0;
}

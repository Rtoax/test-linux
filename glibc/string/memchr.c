#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[3] = {'q','2','3'};

	char *ch = memchr(str, '2', 3);

	printf("%p, %p\n", &str[1], ch);

	char *ch1 = strchr(str, 'q');

	printf("%p, %p\n", &str[0], ch1);
	*ch1 = '0';
	printf("%p, %p\n", &str[0], ch1);

	return 0;
}
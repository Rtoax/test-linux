#include <stdio.h>
#include <stdlib.h>

int test_1(void)
{
	char str[30] = "2030300 This is test";
	char *ptr;
	long ret;

	ret = strtoul(str, &ptr, 10);
	printf("ret = %lu\n", ret);
	printf("|%s|\n", ptr);

	ret = strtoul("11", NULL, 16);
	printf("11 = %ld\n", ret);

	return(0);
}

int main(void)
{
	char *str = "123abc";
	char *ret;

	unsigned long int li = strtoul(str, &ret, 10);

	printf("%s : %ld, %s\n", str, li, ret);

	return 0;
}

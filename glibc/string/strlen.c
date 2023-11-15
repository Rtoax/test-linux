#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


int main(void)
{
	wchar_t str[] = L"Rong Tao say hello\n";

	char str2[10] = {'e','d','c','b','a'};

	printf("%ls, %ld, %ld\n", str, strlen((char*)str), sizeof(str));
	printf("%ls, %ld, %ld\n", str, wcslen(str), sizeof(str));
	printf("%ls, %ld, %ld\n", str, wcsnlen(str, 4), sizeof(str));
	printf("%s, %ld, %ld\n", str2, strlen((char*)str2), sizeof(str2));
	printf("%s, %ld, %ld\n", str2, strnlen((char*)str2, 3), sizeof(str2));

	char *s = NULL;

	if (s && strlen(s) > 0)
		printf("%ld\n", strlen(s));

	char *str3 = "hello";
	printf("strlen(%s) = %ld\n", str3, strlen(str3));

	return 0;
}

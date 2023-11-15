#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[200] = {"Hello World! My name is Rong tao."};

	char *p = strtok(str, "owl");

	printf("%s, %p\n", str, str);
	printf("%s, %p\n", p, p);

	char str2[200] = {"Hello World! My name is Rong tao."};
	char *save_ptr;
	char *p2 = strtok_r(str2, "R", &save_ptr);

	printf("%s, %p\n", str2, str2);
	printf("%s, %p\n", p2, p2);
	printf("%s, %p\n", save_ptr, save_ptr);

	return 0;
}

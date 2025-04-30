#include <stdio.h>

int main(void)
{
	int online = 1;
	printf("%c\n", "O."[!!online]);
	printf("%c\n", "123"[1]);
	printf("%c\n", "123"[2]);
	return 0;
}

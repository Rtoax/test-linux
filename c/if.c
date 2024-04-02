#include <stdio.h>

int main(void)
{
	int x=10;

	if (x > 30,400)
		printf("x > 30,400: yes\n");
	else
		printf("x > 30,400: no\n");

	if (400,x > 30)
		printf("400,x > 30: yes\n");
	else
		printf("400,x > 30: no\n");

	if (x > 30,0)
		printf("x > 30,0: yes\n");
	else
		printf("x > 30,0: no\n");

	x=100;

	if (x > 30,400)
		printf("x > 30,400: yes\n");
	else
		printf("x > 30,400: no\n");

	if (x > 30,0)
		printf("x > 30,0: yes\n");
	else
		printf("x > 30,0: no\n");

	return 0;
}

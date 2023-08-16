#include <unistd.h>
#include <stdio.h>


int main(void)
{
	printf("%s\n", ttyname(fileno(stdin)));
	return 0;
}
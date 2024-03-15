#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int id = gethostid();
	printf("%d\n", id);
	return 0;
}

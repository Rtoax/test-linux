#include <string.h>
#include <stdio.h>

int main(void)
{
	char name1[] = {"xyz"};
	char buf[1024];

	strcpy(buf, name1);

	return 0;
}

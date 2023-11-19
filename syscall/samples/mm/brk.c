#include <unistd.h>
#include <stdio.h>


int main(void)
{
	int *p = NULL;
	brk(p);
	return 0;
}


#include <unistd.h>
#include <stdio.h>


int main(void)
{
	execle("/usr/bin/ls", "-la", NULL, NULL);
	return 0;
}

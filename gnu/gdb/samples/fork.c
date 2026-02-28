#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	fork();
	fork();
	return 0;
}

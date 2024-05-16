#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	long id;

	id = gethostid();
	printf("hostid = %lx\n", id);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

int main(int argc, char *argv[])
{
	symlink(argv[0], "symlink.out");

	return 0;
}

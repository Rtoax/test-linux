#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>

int main(int argc, char **argv)
{
	/* ls | ./splice | cat */
	splice(0, 0, 1, 0, 1 << 30, 0);
	return 0;
}

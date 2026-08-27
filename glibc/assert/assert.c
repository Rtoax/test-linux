#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	assert(1);
#ifdef ERROR
	assert(0);
#endif
	return 0;
}

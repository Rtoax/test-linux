#include <stdio.h>

#include <capstone/capstone.h>


int main(void)
{
	printf("capstone %d.%d.%d\n",
		CS_VERSION_MAJOR, CS_VERSION_MINOR, CS_VERSION_EXTRA);
	return 0;
}

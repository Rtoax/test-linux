#include <stdio.h>
#include <stdlib.h>

#define DO_PRAGMA(x) _Pragma(#x)

int main(void)
{
	DO_PRAGMA(GCC dependency "/etc/os-release")
	return 0;
}

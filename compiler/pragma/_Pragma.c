#include <stdio.h>
#include <stdlib.h>

#define DO_PRAGMA(x) _Pragma(#x)

int main(void)
{
	DO_PRAGMA(GCC dependency "/etc/os-release")
#ifdef ERROR
	DO_PRAGMA(GCC dependency "/etc/__not_exist_file__")
#endif
	return 0;
}

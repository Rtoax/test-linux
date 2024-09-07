#include <stdio.h>
#include <stdlib.h>

#define DO_PRAGMA(x) _Pragma(#x)

int main(void)
{
	/**
	 * Test the timestamps of the current file (i.e., the program code in
	 * which the statement resides) and the specified file (i.e., the file
	 * listed last of the #pragma statement). If the specified file is
	 * newer than the current file, a warning message is given.
	 */
	#pragma GCC dependency "/etc/os-release"
	DO_PRAGMA(GCC dependency "/etc/os-release")
	return 0;
}

/**
 * See also
 *
 * linux include/linux/compiler-gcc.h
 *   #define __diag_str1(s)          #s
 *   #define __diag_str(s)           __diag_str1(s)
 *   #define __diag(s)               _Pragma(__diag_str(GCC diagnostic s))
 *
 * linux include/linux/compiler-clang.h
 *   #define __diag_str1(s)          #s
 *   #define __diag_str(s)           __diag_str1(s)
 *   #define __diag(s)               _Pragma(__diag_str(clang diagnostic s))
 */

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

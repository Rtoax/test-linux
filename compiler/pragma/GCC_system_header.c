/**
 * There is also a directive, #pragma GCC system_header, which tells GCC to
 * consider the rest of the current include file a system header, no matter
 * where it was found. Code that comes before the #pragma in the fle will
 * not be aﬀected. #pragma GCC system_header has no eﬀect in the primary
 * source fle.
 * On very old systems, some of the pre-defned system header directories get
 * even more special treatment. GNU C++ considers code in headers found in
 * those directories to be surrounded by an extern "C" block. There is no way
 * to request this behavior with a #pragma, or from the command line.
 */

#include <stdio.h>
#include <stdlib.h>

#include <system_header.h>

int main(void)
{
	printf("Hello\n");
	return 0;
}

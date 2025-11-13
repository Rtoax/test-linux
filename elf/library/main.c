#include <stdio.h>
#include <unistd.h>
#include "foo.h"
#include "thread.h"

int main(void)
{
	foo();
#if defined(CALL_FUNC_IN_OBJ)
	/**
	 * Only call this function, the ctors in relate object source code
	 * can be called. Otherwise, the ctors will not be called.
	 */
	foo_ctor();
#endif
	thread_hello();

	getchar();

	return 0;
}

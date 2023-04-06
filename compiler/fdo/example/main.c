/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"

unsigned long
FN(test_add)(void);

int main()
{
#if defined(TEST_SORT)
	CALL(start)();
	CALL(sort_array)(30000);
	CALL(stop)();

#elif defined(TEST_ADD)

	CALL(start)();
	CALL(test_add)();
	CALL(stop)();
#endif

	return 0;
}


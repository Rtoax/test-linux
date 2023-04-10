/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"

unsigned long test_add(void);
unsigned long test_branch(void);

int main()
{
#if defined(TEST_SORT)
	start();
	sort_array(30000);
	stop();

#elif defined(TEST_ADD)

	start();
	test_add();
	stop();

#elif defined(TEST_BRANCH)

	start();
	test_branch();
	stop();
#endif

	return 0;
}


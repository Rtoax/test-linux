/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"


int main()
{
	CALL(start)();
	CALL(sort_array)(30000);
	CALL(stop)();

	return 0;
}


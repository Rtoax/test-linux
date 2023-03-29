/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"


int main()
{
	FN(start)();
	FN(sort_array)(30000);
	FN(stop)();

	return 0;
}


/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"


int main()
{
	start();
	sort_array(30000);
	stop();

	return 0;
}


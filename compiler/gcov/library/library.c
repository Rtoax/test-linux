#include <stdio.h>

#include "library.h"


DEFINE_FN1(branch_1st)
DEFINE_FN1(branch_2nd)
DEFINE_FN1(branch_3rd)
DEFINE_FN1(branch_4th)
DEFINE_FN1(branch_5th)
DEFINE_FN1(branch_6th)
DEFINE_FN1(branch_7th)

#define LIB_BRANCH_FN lib_branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

int lib_f1(void)
{
	lib_branch_f1(100000);

	return 0;
}


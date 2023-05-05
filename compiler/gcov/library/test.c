#include "library.h"

#define LIB_BRANCH_FN branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

int main(void)
{
	branch_f1(100000);

	return lib_f1();
}


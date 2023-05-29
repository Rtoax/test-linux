
#ifndef LIB_BRANCH_FN
# error Undefined LIB_BRANCH_FN
#endif

unsigned long __noinline__
LIB_BRANCH_FN(unsigned long a)
{
	unsigned long i, ret = 0;

	/**
	 * I deliberately put the number of function calls in reverse order
	 * of branching statements, and FDO will optimize the ordering of
	 * branching statements.
	 */
	for (i = 0; i < a; i++) {
		if (i % 400 == 1)
			ret += fn1_branch_7th(i);
		else if (i % 300 == 2)
			ret += fn1_branch_6th(i);
		else if (i % 200 == 3)
			ret += fn1_branch_5th(i);
		else if (i % 100 == 4)
			ret += fn1_branch_4th(i);
		else if (i % 50 == 5)
			ret += fn1_branch_3rd(i);
		else if (i % 10 == 6)
			ret += fn1_branch_2nd(i);
		else if (i % 2 == 1)
			ret += fn1_branch_1st(i);
		else
			ret += 1;
	}

	return ret;
}

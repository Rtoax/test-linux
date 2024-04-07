#include <stdio.h>
#include "tests.h"

static struct test *tests[100];
static int nr_tests = 0;

void add_test(struct test *t)
{
	tests[nr_tests++] = t;
}

int main(void)
{
	int i;
	struct test *t;

	for (i = 0; i < nr_tests; i++) {
		t = tests[i];
		printf("%s\n", t->name);
		t->init();
		t->run();
		t->fini();
	}

	return 0;
}

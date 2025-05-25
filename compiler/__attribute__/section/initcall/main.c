#include <stdio.h>
#include "log.h"
#include "init.h"

struct test __data t1 = {
		.name = "t1",
		.i = 1,
	};
struct test __data t2 = {
		.name = "t2",
		.i = 2,
	};


void __attribute__((constructor)) do_init(void)
{
	init_call *call_ptr = &init_start;
	while (call_ptr && call_ptr < &init_end) {
		(*call_ptr)();
		++call_ptr;
	}

	/**
	 * WARNING: must be align
	 */
	struct test *t = &data_start;
	while (t && t < &data_end) {
		printf("%s %d\n", t->name, t->i);
		++t;
	}
}

int init_1(void)
{
	log("\n");
}
INIT(init_1);

int init_2(void)
{
	log("\n");
}
INIT(init_2);

int main(void)
{
	return 0;
}

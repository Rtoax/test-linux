#include <stdio.h>
#include "log.h"
#include "init.h"


void __attribute__((constructor)) do_initcalls(void)
{
	init_call *call_ptr = &init_start;
	while (call_ptr && call_ptr < &init_end) {
		(*call_ptr)();
		++call_ptr;
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

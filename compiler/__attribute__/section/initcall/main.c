#include <stdio.h>
#include "log.h"
#include "init.h"


extern init_call init_start;
extern init_call init_end;

void do_initcalls(void)
{
	init_call *call_ptr = &init_start;
	while (call_ptr && call_ptr < &init_end) {
		fprintf (stderr, "call_ptr: %p\n", call_ptr);
		(*call_ptr)();
		++call_ptr;
	};
}

int init_main1()
{
	log("rongtao1\n");
}

int init_main2()
{
	log("rongtao2\n");
}

INIT(init_main1);
INIT(init_main2);

int main(void)
{
	printf("boot = %d\n", 0);
	do_initcalls();
}

#include <stdio.h>
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
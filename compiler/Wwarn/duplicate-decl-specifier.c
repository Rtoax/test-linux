#include <stdio.h>
#include <stdint.h>

#define __seg_gs                __attribute__((address_space(256)))
#define __percpu_seg_override   __seg_gs

#define __my_cpu_type(var)      typeof(var)
#define __my_cpu_ptr(ptr)       (__my_cpu_type(*(ptr))*)(uintptr_t)(ptr)

#define __raw_cpu_read(qual, pcp) ({ *(qual __my_cpu_type(pcp) *)__my_cpu_ptr(&(pcp)); })

#define this_cpu_read_const(pcp) __raw_cpu_read(, pcp)

int main(void)
{
	const volatile int a = 1;
	int b;

	b = this_cpu_read_const(a);

	(void)b;

	return 0;
}


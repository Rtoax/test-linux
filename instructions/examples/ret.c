#include <stdio.h>

#define ret_x86_64_v1(__val)	__asm__("mov $"#__val", %rax; ret");
#define ret_x86_64_v2(val) ({				\
	register unsigned long __ret asm("rax") = val;	\
	__asm__ volatile("ret" : : "r"(__ret));		\
	})

#if 1
#define ret_x86_64_TODO(val) ({			\
	__asm__ volatile("mov %0, %%rax \n\t"	\
		"ret"				\
		: /* no return */		\
		: "r"(val)			\
		: "rax", "memory");		\
	})
#endif

#define ret_aarch64(__val)	__asm__("mov x0, #"#__val"; ret");

#if defined(__x86_64__)
#define RETURN(v) ret_x86_64_v2(v)
#elif defined(__aarch64__)
#define RETURN(v) ret_aarch64(v)
#else
#define RETURN(v) return v
#endif

#define _omit_frame_pointer  __attribute__((optimize("omit-frame-pointer")))

int _omit_frame_pointer func1(void)
{
	RETURN(1);
}

int _omit_frame_pointer func2(void)
{
	RETURN(0xffffffff);
}

int _omit_frame_pointer func3(void)
{
	RETURN(-1);
}

long _omit_frame_pointer func4(void)
{
	RETURN(0xfffffffff);
}

int main(void)
{
	printf("func1 return %d\n", func1());
	printf("func2 return %d\n", func2());
	printf("func3 return %d\n", func3());
	printf("func4 return %lx\n", func4());
	return 0;
}

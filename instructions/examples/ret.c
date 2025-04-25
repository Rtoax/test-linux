#include <stdio.h>

#define ret_x86_64(__val)	__asm__("mov $"#__val", %rax; ret");

#define ret_x86_64_TODO(__val) ({		\
	long __rslt;			\
	__asm__("mov %1, %%rax \n\t"	\
		"mov %%rax, %0 \n\t"	\
		"ret \n\t"		\
		: "=r"(__rslt)		\
		: "r"(__val)		\
		: "%%rax");		\
	__rslt;				\
	})

#if defined(__x86_64__)
#define RETURN(v) ret_x86_64(v)
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
	RETURN(2);
}

int _omit_frame_pointer func3(void)
{
	RETURN(3);
}

int main(void)
{
	printf("func1 return %d\n", func1());
	printf("func2 return %d\n", func2());
	printf("func3 return %d\n", func3());
	return 0;
}

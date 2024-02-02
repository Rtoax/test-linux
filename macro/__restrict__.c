/**
 * c语言限定符，告诉编译器，对象已经被指针所引用，不能通过除该指针外所有其他直
 * 接或间接的方式修改该对象的内容
 */

#include <stdio.h>

void fn (int *__restrict__ rptr, int* __restrict__ rref)
{
#if 0
	int *p  = rptr;
	*p = 12;
#else
	*rptr = 12;
#endif
}

int main(void)
{
	int buffer[12];
	int *p1, *p2;
	p1 = p2 = buffer;
	fn(p1, p2);
	return 0;
}

#include <stdio.h>

#define DEF_STACK_DATA(name) char __attribute__((unused)) name[64] = {"A"}

#define CALL(func, count) do {	\
		int ___i;	\
		for (___i = 0; ___i < count; ___i++)	\
			func();	\
	} while (0)

int A(void);
int B(void);
int C(void);
int D(void);

int A(void) {
	DEF_STACK_DATA(a);
	CALL(C, 100);
	return 0;
}

int B(void) {
	DEF_STACK_DATA(b);
	CALL(D, 1);
	return 0;
}

int C(void) {
	DEF_STACK_DATA(c);
	CALL(D, 100);
	return 0;
}

int D(void) {
	DEF_STACK_DATA(d);
	return 0;
}

int main(void)
{
	printf("Hello World!\n");
	return 0;
}

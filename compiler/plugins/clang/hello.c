#ifdef TEST_PID
#include <stdio.h>

extern int pid;

void test_pid(void)
{
	printf("pid = %d\n", pid);
}
#else
#define test_pid()
#endif

#ifdef TEST_ATTRIBUTE
void fn1(void) __attribute__((example)) {
	__attribute__((example("abc", 3, 4.0))) for (int i = 0; i < 9; ++i) {}
}
#endif

int main(void)
{
	test_pid();
	return 0;
}

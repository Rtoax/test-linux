#include <stdio.h>


typedef int (*fn_t)(void);

typedef struct {
	int value;
	fn_t getValue;
}text_t;


int __getValue(void)
{
	/**
	 * 显然这个地址不是全局变量的地址，这只是一个函数栈帧的结束地址
	 */
	text_t *t = __builtin_return_address(0);
	printf("getValue: %d\n", t->value);
	return t->value;
}

text_t t1 = {1, __getValue};

text_t* test(void)
{
	printf("%d\n", t1.getValue());
	return &t1;
}

int main(void)
{
	test();
}
#include <stdio.h>

typedef struct {
	int value;
	int (*getValue)(void);
} text_t;


int __getValue(void)
{
	/**
	 * TODO: Wrong 'this' pointer
	 */
	void *ret_addr = __builtin_return_address(0);
	text_t *this = (void *)(ret_addr - sizeof(void *));
	return this->value;
}

text_t t1 = { 1, __getValue };
text_t t2 = { 2, __getValue };

int main(void)
{
	printf("%d\n", t1.getValue());
	printf("%d\n", t2.getValue());
	return 0;
}

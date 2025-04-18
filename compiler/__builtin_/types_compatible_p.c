#include <stdio.h>
#include <stdlib.h>


void show_c(char a)
{
	printf("char: %c\n", a);
}

void show_f(float a)
{
	printf("float: %f\n", a);
}

#define _C(a, b) __builtin_types_compatible_p(a, b)
#define _E(exp, e1, e2) __builtin_choose_expr(exp, e1, e2)
#define show(a) \
	_E(_C(typeof(a), char), show_c(a), \
		_E(_C(typeof(a), float), show_f(a), printf("nothing\n")))

int main(void)
{
	show('a');
	show((int)'a');
	show((char)'a');
	show((float)'a');
	return 0;
}

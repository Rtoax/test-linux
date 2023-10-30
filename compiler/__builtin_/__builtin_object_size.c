#include <stdio.h>
#include <assert.h>

int main(void)
{

	struct V {
		char buf1[10];
		int b;
		char buf2[10];
	} var;

	char *p = &var.buf1[1], *q = (void*)&var.b;
	char *r = NULL;

	printf("%d\n", __builtin_object_size(p, 0));
	printf("%d\n", __builtin_object_size(p, 1));
	printf("%d\n", __builtin_object_size(p, 2));
	printf("%d\n", __builtin_object_size(p, 3));
	printf("%d\n", __builtin_object_size(q, 0));
	printf("%d\n", __builtin_object_size(q, 1));
	printf("%d\n", __builtin_object_size(q, 2));
	printf("%d\n", __builtin_object_size(q, 3));
	printf("%d\n", __builtin_object_size(r, 0));


	char b[10];
	char *c = &b[5];

	printf("%d\n", __builtin_object_size(b, 0));
	printf("%d\n", __builtin_object_size(b, 1));
	printf("%d\n", __builtin_object_size(b, 2));
	printf("%d\n", __builtin_object_size(b, 3));
	printf("%d\n", __builtin_object_size(c, 0));

	return 0;
}

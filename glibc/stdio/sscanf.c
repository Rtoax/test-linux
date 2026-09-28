#include <stdio.h>
#include <stdlib.h>

void test_float(void)
{
	struct test_f {
		char *s;
		float f;
	} tests[] = {
		{ "1", 1.f },
		{ "3.14", 3.14f },
		{ "9.26536e-05", 9.26536e-05 },
		{ "-0.207815", -0.207815 },
	};

	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
		float a;
		sscanf(tests[i].s, "%f", &a);
		printf("%f vs %f\n", a, tests[i].f);
	}
}

int main(int argc, char *argv[])
{
	int a, b;
	char str[256];

	sscanf("1.2", "%d.%d\n", &a, &b);
	printf("%d, %d\n", a, b);

	sscanf("3 4", "%s\n%d\n", str, &b);
	printf("%s, %d\n", str, b);

	test_float();

	return 0;
}

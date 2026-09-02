#include <stdio.h>
#include <ctype.h>

void test(char ch)
{
#define T(func) \
	printf("%16s(%c) = %s\n", #func, ch, func(ch) ? "true" : "false")
	T(isalpha);
	T(islower);
	T(isupper);
	T(isdigit);
	T(isalnum);
	T(isxdigit);
	T(ispunct);
	T(isspace);
	T(isblank);
	T(isgraph);
	T(isprint);
	T(iscntrl);
	T(isascii);
#undef T
}

int main(int argc, char *argv[])
{
	char data[] = { "1aA_=? \t\n\b" };

	for (int i = 0; i < sizeof(data); i++)
		test(data[i]);

	return 0;
}

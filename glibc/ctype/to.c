#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char data[] = { "1aA_=?" };

	for (int i = 0; i < sizeof(data); i++) {
		char ch = data[i];
#define T(func) printf("%16s('%c') = '%c'\n", #func, ch, func(ch))
		T(tolower);
		T(toupper);
		T(toascii);
		T(_tolower);
		T(_toupper);
#undef T
	}

	return 0;
}

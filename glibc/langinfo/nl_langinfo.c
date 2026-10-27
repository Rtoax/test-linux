#include <stdio.h>
#include <locale.h>
#include <langinfo.h>

int main(void)
{
	setlocale(LC_CTYPE, "");
	setlocale(LC_NUMERIC, "");

#ifdef ALL
	for (int i = 0; i < _NL_NUM; i++) {
		printf("%s\n", nl_langinfo(i));
	}
#endif

	printf("%s\n", nl_langinfo(CODESET));
	printf("%s\n", nl_langinfo(RADIXCHAR));

	return 0;
}

#include <stdio.h>
#include <stddef.h> /* wchar_t */
#include <wctype.h>

int main(void)
{
	wchar_t wc = L'2';

	if (iswctype(wc, wctype("digit")))
		printf("iswctype\n");

	return 0;
}

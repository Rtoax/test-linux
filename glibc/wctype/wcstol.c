#include <stdio.h>
#include <stddef.h> /* wchar_t */
#include <wctype.h>
#include <wchar.h>

int main(void)
{
	wchar_t *wc = L"123abc";
	wchar_t *ret;

	unsigned long l = wcstol(wc, &ret, 10);

	wprintf(L"%w %d\n", ret, l);

	return 0;
}

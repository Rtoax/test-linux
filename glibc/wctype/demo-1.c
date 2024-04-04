#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <string.h>

/**
 * typedef unsigned long int wctype_t;
 *
 * "alnum" "alpha" "cntrl" "digit" "graph" "lower" "print" "punct" "space"
 * "upper" "xdigit"
 */

int is_in_class1(int c, const char *class)
{
	if(strcmp(class, "alnum") == 0)
		return isalnum(c);
	if(strcmp(class, "alpha") == 0)
		return isalpha(c);
	if(strcmp(class, "cntrl") == 0)
		return iscntrl(c);

	return 0;
}

int is_in_class2(int c, const char *class)
{
	wctype_t desc = wctype(class);
	return desc ? iswctype(btowc(c), desc) : 0;
}

int main(void)
{
	wchar_t str[] = L"C/C++ Python Swift Java Golang\n";
	wchar_t c;
	wctype_t check  = wctype("upper");
	wctrans_t trans = wctrans("tolower");
	int i;

	i = 0;
	while (str[i]) {
		c = str[i];

		if (iswctype(c, check)) {
			c = towctrans(c, trans);
		}
		putwchar(c);
		i++;
	}

	i = 0;
	while (str[i]) {
		c = str[i];
		if (is_in_class2(c, "lower")) {
			c = toupper(c);
		}
		putwchar(c);
		i++;
	}
	printf("size of c = %ld\n", sizeof(c));

	return 0;
}

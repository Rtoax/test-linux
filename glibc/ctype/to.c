#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char ch = argv[1][0];

	printf("%c\n", ch);

	printf("tolower: %c\n", tolower(ch));
	printf("toupper: %c\n", toupper(ch));
	printf("toascii: %c\n", toascii(ch));
	printf("_tolower: %c\n", _tolower(ch));
	printf("_toupper: %c\n", _toupper(ch));

	return 0;
}

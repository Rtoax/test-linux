#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char ch;

	if (argc > 1)
		ch = argv[1][0];
	else
		ch = 'x';

	printf("%c\n", ch);

	if (isalpha(ch))
		printf("isalpha\n");
	if (islower(ch))
		printf("islower\n");
	if (isupper(ch))
		printf("isupper\n");
	if (isdigit(ch))
		printf("isdigit\n");
	if (isalnum(ch))
		printf("isalnum\n");
	if (isxdigit(ch))
		printf("isxdigit\n");
	if (ispunct(ch))
		printf("ispunct\n");
	if (isspace(ch))
		printf("isspace\n");
	if (isblank(ch))
		printf("isblank\n");
	if (isgraph(ch))
		printf("isgraph\n");
	if (isprint(ch))
		printf("isprint\n");
	if (iscntrl(ch))
		printf("iscntrl\n");
	if (isascii(ch))
		printf("isascii\n");

	return 0;
}

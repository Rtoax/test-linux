#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
#define S(ch)                                           \
	printf("%6s is%s space, %6s is%s blank\n", #ch, \
	       isspace(ch) ? "" : " not", #ch, isblank(ch) ? "" : " not")

	S(' ');
	S('\0');
	S('\t');
	S('\r');
	S('\n');
	S('\b');
	S('\f');
	S('\v');
	S('a');

	return 0;
}

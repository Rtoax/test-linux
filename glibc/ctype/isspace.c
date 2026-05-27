#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
#define S(ch) printf("%-4s is%s space\n", #ch, isspace(ch) ? "" : " not");

	S(' ');
	S('\0');
	S('\t');
	S('\r');
	S('\n');
	S('\b');
	S('a');

	return 0;
}

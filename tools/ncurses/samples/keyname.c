#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	for (int i = 0; i < 256; i++)
		printf("keyname(%d) = %s\n", i, keyname(i));
	return 0;
}

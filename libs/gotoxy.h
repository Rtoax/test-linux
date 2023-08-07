#include <stdio.h>

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

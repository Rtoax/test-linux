#include "gotoxy.h"

int main(void)
{
	int i;
	for (i = 0; i < 10; i++) {
		gotoxy(i, i);
		printf("\033[1;31m#\033[m");
	}
	printf("\n\n");
	return 0;
}

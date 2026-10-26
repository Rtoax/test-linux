#include <stdio.h>
#include <utmpx.h>

int main(void)
{
	setutxent();
	endutxent();
	return 0;
}

#include <stdio.h>
#include <utmp.h>

int main(void)
{
	setutent();
	endutent();
	return 0;
}

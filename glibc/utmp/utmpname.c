#include <utmp.h>
#include <stdio.h>

int main(void)
{
	utmpname("/var/log/wtmp");

	return 0;
}

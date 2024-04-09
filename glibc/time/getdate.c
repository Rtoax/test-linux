#include <stdio.h>
#include <time.h>
#include <string.h>


int main(void)
{
	struct tm __attribute__((unused)) *t;

	t = getdate("Thursday Thu January Jan 19 Thu Jan  1 08:00:01 1970 %");

	return 0;
}

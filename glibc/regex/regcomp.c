#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(void)
{
	regex_t rt;

	regcomp(&rt, "{./}{, *.c, tao}", REG_EXTENDED);

	return 0;
}

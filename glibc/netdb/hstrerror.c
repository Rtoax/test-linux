#include <stdio.h>
#include <netdb.h>

int main(void)
{
	printf("%s\n", hstrerror(h_errno));
	return 0;
}

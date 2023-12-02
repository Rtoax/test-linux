#include <stdio.h>
#include <malloc.h>
#include <unistd.h>


/**
 * x86_64: R_X86_64_64
 */
int gin;
int gii = 1;
static int gsin;
static int gsii = 1;
void *gp;

int main(void)
{
	void *p;

	/**
	 * x86_64: R_X86_64_PLT32
	 */
	puts("Hello\n");
	p = malloc(1024);
	free(p);

	return 0;
}

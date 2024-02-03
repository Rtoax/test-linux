#include <stdio.h>
#include <jemalloc/jemalloc.h>

void my_stats_print(void *cbopaque, const char *s)
{
	char *hint = (char*)cbopaque;
	printf("%s>> %s\n", hint, s);
}

int main(void)
{
	int *I = mallocx(1024, MALLOCX_LG_ALIGN(8));
	char print_hint[] = {"Hint"};

	printf("##########General information that never changes during execution############\n");
	malloc_stats_print(my_stats_print, print_hint, "Jg");

	printf("##########merged arena############\n");
	malloc_stats_print(my_stats_print, print_hint, "Jm");

	free(I);
}

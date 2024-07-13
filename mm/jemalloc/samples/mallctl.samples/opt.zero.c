#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.zero (bool) r- [--enable-fill]
//	Zero filling enabled/disabled. If enabled, each byte of uninitialized allocated memory will be initialized to 0. Note
//	that this initialization only happens once for each byte, so realloc() and rallocx() calls do not zero memory that
//	was previously allocated. This is intended for debugging and will impact performance negatively. This option is
//	disabled by default.

void get_jemalloc_opt_zero(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.zero", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_zero(&enable);
	printf("enable = %d\n", enable);

	unsigned char *str = je_malloc(1);
	printf("%x\n", *str);


}




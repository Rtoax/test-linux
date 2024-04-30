#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *p1 = malloc(1039);

	/**
	 * these functions are removed in glibc 2.25
	 */
#if __GLIBC__ <= 2 && __GLIBC_MINOR__ < 25
	char *state = malloc_get_state();
	if (state) {
		printf("state %p\n", state);
	}

	int ret = malloc_set_state(state);
	printf("ret %d\n", ret);
#endif
	free(p1);
}


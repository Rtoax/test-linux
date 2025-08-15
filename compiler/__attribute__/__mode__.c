#include <stdio.h>

/* see /usr/include/bits/floatn-common.h */
typedef float fp16_t __attribute__ ((__mode__ (__HF__)));

int main(void)
{
	printf("size of fp16_t is %ld\n", sizeof(fp16_t));
	return 0;
}

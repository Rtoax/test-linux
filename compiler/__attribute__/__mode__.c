#include <stdio.h>

/**
 * see /usr/include/bits/floatn-common.h
 * typedef float _Float16 __attribute__ ((__mode__ (__HF__)));
 */
#if !__GNUC_PREREQ(7, 0) || (defined __cplusplus && !__GNUC_PREREQ(13, 0))
#define have_mode_HF 1
#endif

#ifdef have_mode_HF
typedef float fp16_t __attribute__ ((__mode__ (__HF__)));
#endif

int main(void)
{
#ifdef have_mode_HF
	printf("size of fp16_t is %ld\n", sizeof(fp16_t));
#endif
	return 0;
}

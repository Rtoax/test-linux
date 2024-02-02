#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
# define __func__ __FUNCTION__
# else
# define __func__ "<unknown>"
# endif
#endif

#include <stdio.h>

int main(void)
{
	printf("__func__ = %s\n", __func__);
	return 0;
}

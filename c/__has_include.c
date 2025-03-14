#include <stdio.h>

#ifdef __has_include
# if __has_include (<stdatomic.h>)
#  include <stdatomic.h>
#  pragma message "Include stdatomic.h"
# endif
#endif

int main(void)
{
	return 0;
}

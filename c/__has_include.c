#include <stdio.h>

#ifdef __has_include
# if __has_include (<stdatomic.h>)
#  include <stdatomic.h>
#  pragma message "found and include stdatomic.h"
# endif
#else
# pragma warning "compiler not support __has_include"
#endif

#ifdef __has_feature
# if __has_feature(gnu_inline)
#  pragma message "compiler support gnu_inline feature"
# endif
#else
# pragma warning "compiler not support __has_feature"
#endif

#ifdef __has_extension
# if __has_extension(blocks)
#  pragma message "compiler support blocks extension"
# endif
#else
# pragma warning "compiler not support __has_extension"
#endif

int main(void)
{
	return 0;
}

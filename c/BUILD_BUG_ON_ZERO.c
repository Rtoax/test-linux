#include <stdio.h>

#define BUILD_BUG_ON_ZERO(e) (void)(sizeof(struct { int:-!!(e); }))
#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))

int main(void)
{
	BUILD_BUG_ON_ZERO(0);

	return 0;
}

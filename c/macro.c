#include <stdio.h>
#include "unused.h"

struct attr {
	void (*show)(void);
};

#define __ATTR_RO(_name) {		\
	.show = _name##_show		\
}

#define ATTR_RO(_name)	\
	struct attr attr_##_name = __ATTR_RO(_name)

void print_show(void) { }

static __unused ATTR_RO(print);

#if CONFIG_MMU == y
#pragma message "Defined CONFIG_MMU=y"
#endif

int main(void)
{
	return 0;
}
